#include <QtCore>
#include "traffic.hpp"


// --------------------------------------------------
// TrafficInfo
// --------------------------------------------------
TrafficInfo::TrafficInfo ()
{
}


// --------------------------------------------------
// ExtendedTrafficInfo
// --------------------------------------------------
ExtendedTrafficInfo::ExtendedTrafficInfo ()
{
}


// --------------------------------------------------
// Traffic
// --------------------------------------------------
Traffic::Traffic ()
    : QObject ()
{
    connect (&_fetcher, SIGNAL (done (const QByteArray&)),
             SLOT (fetchDone (const QByteArray&)));
}

// Perform asyncronous refresh of traffic information. If another update
// request is in progress, new is discarded. If update request finished
// successfully, updated() signal called.
void Traffic::update ()
{
    if (_fetcher.busy ())
        return;

    _fetcher.fetch ("http://trf.maps.yandex.net/trf/stat.xml");
}


void Traffic::fetchDone (const QByteArray& data)
{
    printf ("Got %d bytes of data\n", data.size ());
//    printf ("Data:\n%s\n", data.data ());
    updated ();
}

