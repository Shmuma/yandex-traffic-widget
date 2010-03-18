#include <QtDBus>

#include "connection.hpp"
#include "icd2_light.h"
#include "log.hpp"

static ConnectionChecker *_instance = NULL;


// --------------------------------------------------
// ConnectionChecker singleton
// --------------------------------------------------
ConnectionChecker *ConnectionChecker::instance ()
{
    if (!_instance)
        _instance = new ConnectionChecker;
    return _instance;
}


ConnectionChecker::ConnectionChecker ()
    : _bus (QDBusConnection::systemBus ())
{
    _connected = true;

    _itf = new QDBusInterface (ICD_DBUS_API_INTERFACE, ICD_DBUS_API_PATH, ICD_DBUS_API_INTERFACE, _bus);
    _bus.connect (ICD_DBUS_API_INTERFACE, ICD_DBUS_API_PATH, ICD_DBUS_API_INTERFACE, ICD_DBUS_API_STATE_SIG,
                  this, SLOT (stateSignal (const QDBusMessage&)));
    _conn_counter = 0;

    requestState ();
}


void ConnectionChecker::requestState ()
{
    QDBusMessage reply = _itf->call (ICD_DBUS_API_STATE_REQ);

    // If there is no connection, we get no reply at all
    if (!reply.arguments ().value (0).toUInt ())
        updateState (false);
}


void ConnectionChecker::stateSignal (const QDBusMessage& msg)
{
    if (msg.arguments ().count () != 8)
        return;

    unsigned int state = msg.arguments ().value (7).value<unsigned int>();
    QString net = msg.arguments ().value (3).toString ();

    if (state == ICD_STATE_CONNECTED)
        _conn_counter++;
    if (state == ICD_STATE_DISCONNECTED)
        _conn_counter--;

    Log::instance ()->add (QString ("stateSignal: state = %1, net = %2, counter = %3").arg (state).arg (net).arg (_conn_counter));

    if (state == ICD_STATE_CONNECTED || !_conn_counter)
        updateState (state == ICD_STATE_CONNECTED, net);
}


void ConnectionChecker::updateState (bool new_state, const QString& net_type)
{
    network_type_t new_net = Net_None;

    Log::instance ()->add (QString ("ConnectionChecker::updateState (%1, %2)").arg (new_state ? "connected" : "not connected").arg (net_type));

    if (new_state != _connected) {
        _connected = new_state;
        emit connected (_connected);
    }

    if (_connected) {
        if (net_type.startsWith ("WLAN"))
            new_net = Net_WLAN;
        else if (net_type.startsWith ("GPRS") || net_type.startsWith ("DUN_GSM"))
            new_net = Net_GSM;
    }

    if (new_net != _net_type) {
        _net_type = new_net;
        type_changed (_net_type);
    }
}


bool ConnectionChecker::checkConnection (bool allow_gsm, bool allow_wifi)
{
    if (!_connected)
        return false;

    switch (_net_type) {
        case Net_None:
            Log::instance ()->add ("checkConnection: Net_None, allow");
            return true;
        case Net_WLAN:
            Log::instance ()->add (QString ("checkConnection: Net_WLAN, allow = %1").arg (allow_wifi ? "true" : "false"));
            return allow_wifi;
        case Net_GSM:
            Log::instance ()->add (QString ("checkConnection: Net_GSM, allow = %1").arg (allow_gsm ? "true" : "false"));
            return allow_gsm;
        default:
            Log::instance ()->add ("checkConnection: unknown, allow");
            return true;
    }
}
