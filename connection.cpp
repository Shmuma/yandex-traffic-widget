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
    QDBusMessage msg = QDBusMessage::createSignal (ICD_DBUS_API_PATH, ICD_DBUS_API_INTERFACE, ICD_DBUS_API_STATE_REQ);

    _bus.send (msg);
}


void ConnectionChecker::stateSignal (const QDBusMessage& msg)
{
    unsigned int status = msg.arguments ().value (7).value<unsigned int>();

    if (status == ICD_STATE_CONNECTED) {
        if (!_connected) {
            _connected = true;
            emit connected (true);
        }
    }
    else {
        if (_connected) {
            _connected = false;
            emit connected (false);
        }
    }
}
