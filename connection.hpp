#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <QtCore>


// Singleton, which periodically checks for connection state and notifies when it changed.
class ConnectionChecker : public QObject
{
    Q_OBJECT

private:
    ConnectionChecker ();

protected:
    void timerEvent (QTimerEvent *event);

public:
    static ConnectionChecker *instance ();

signals:
    void connected (bool active);
};

#endif // __CONNECTION_H__
