#include <QtDBus>

#include "connection.hpp"
#include "icd2_light.h"


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
    if (msg.arguments ().count () == 8) {
        unsigned int status = msg.arguments ().value (7).value<unsigned int>();

        updateState (status == ICD_STATE_CONNECTED, msg.arguments ().value (3).toString ());
    }
}


void ConnectionChecker::updateState (bool new_state, const QString& net_type)
{
    network_type_t new_net = Net_None;

    if (new_state != _connected) {
        _connected = new_state;
        emit connected (_connected);
    }

    if (_connected) {
        if (net_type.startsWith ("WLAN"))
            new_net = Net_WLAN;
        else if (net_type.startsWith ("GPRS") || net_type.startsWith ("DUN_GSM"))
            new_net = Net_GSM;
        if (new_net != _net_type) {
            _net_type = new_net;
            type_changed (_net_type);
        }
    }
}
