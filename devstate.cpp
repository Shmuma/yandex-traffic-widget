#include <QtDBus>

#include "devstate.hpp"

#ifdef Q_WS_MAEMO_5
#include <mce/dbus-names.h>
#include <mce/mode-names.h>

#define MCE_AVAILABLE 1
#else
#define MCE_AVAILABLE 0
#endif

static DeviceState *_instance = NULL;


// --------------------------------------------------
// DeviceState
// --------------------------------------------------
DeviceState* DeviceState::instance ()
{
    if (!_instance)
        _instance = new DeviceState;
    return _instance;
}


DeviceState::DeviceState ()
    : _bus (QDBusConnection::systemBus ())
{
    _locked = false;

#if MCE_AVAILABLE
    _itf = new QDBusInterface (MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, _bus);
    _bus.connect (MCE_SERVICE, MCE_SIGNAL_PATH, MCE_SIGNAL_IF, MCE_TKLOCK_MODE_SIG,
                  this, SLOT (tkLockMessage (const QDBusMessage&)));
    requestState ();
#endif
}


void DeviceState::requestState ()
{
#if MCE_AVAILABLE
    tkLockMessage (_itf->call (MCE_TKLOCK_MODE_GET));
#endif
}


void DeviceState::tkLockMessage (const QDBusMessage &msg)
{
#if MCE_AVAILABLE
    QString s;

    if (msg.arguments ().count () > 0) {
        s = msg.arguments ().value (0).toString ();
        printf ("Reply = %s\n", s.toUtf8 ().data ());
        setLocked (s == QString (MCE_TK_LOCKED));
    }
#endif
}


void DeviceState::setLocked (bool new_val)
{
    if (_locked != new_val) {
        _locked = new_val;
        lockChanged (_locked);
    }
}
