#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QtCore>
#include <QtDBus>


// Singleton, which listens for ICD DBUS events about connection change
class ConnectionChecker : public QObject
{
    Q_OBJECT

private:
    bool _connected;
    QDBusConnection _bus;
    QDBusInterface *_itf;

protected:
    ConnectionChecker ();

    void updateState (bool new_state);

protected slots:
    void stateSignal (const QDBusMessage& msg);

public:
    static ConnectionChecker *instance ();

    bool isConnected () const
    { return _connected; };

    void requestState ();

signals:
    void connected (bool active);
};

#endif // __CONNECTION_H__
