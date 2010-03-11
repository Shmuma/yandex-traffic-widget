#ifndef __DEVSTATE_H__
#define __DEVSTATE_H__

#include <QtCore>
#include <QtDBus>


// Singleton which handles device lock state (and, possibly, other MCE stuff)
class DeviceState : public QObject
{
    Q_OBJECT

private:
    bool _locked;

    QDBusConnection _bus;
    QDBusInterface *_itf;

protected:
    DeviceState ();

    void setLocked (bool new_val);

protected slots:
    void tkLockMessage (const QDBusMessage &msg);

public:
    static DeviceState *instance ();

    bool locked () const
    { return _locked; };

    void requestState ();

signals:
    void lockChanged (bool locked);
};

#endif // __DEVSTATE_H__
