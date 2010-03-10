#include "connection.hpp"

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
{
    // start timer which will check connection
    startTimer (15*1000);
}


void ConnectionChecker::timerEvent (QTimerEvent *)
{
    // check for connection
}
