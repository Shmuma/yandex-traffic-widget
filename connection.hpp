#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QtCore>
#include <QtDBus>


// Singleton, which listens for ICD DBUS events about connection change
class ConnectionChecker : public QObject
{
    Q_OBJECT

public:
    enum network_type_t {
        Net_None,
        Net_WLAN,
        Net_GSM,
    };

private:
    bool _connected;
    network_type_t _net_type;

    QDBusConnection _bus;
    QDBusInterface *_itf;

protected:
    ConnectionChecker ();

    void updateState (bool new_state, const QString& net_type = QString ());

protected slots:
    void stateSignal (const QDBusMessage& msg);

public:
    static ConnectionChecker *instance ();

    bool isConnected () const
    { return _connected; };

    network_type_t network_type () const
    { return _net_type; };

    void requestState ();

signals:
    void connected (bool active);
    void type_changed (ConnectionChecker::network_type_t type);
};

#endif // __CONNECTION_H__
