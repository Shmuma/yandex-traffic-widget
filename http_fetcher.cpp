#include <QtCore>
#include <QtNetwork>

#include "http_fetcher.hpp"
#include "connection.hpp"
#include "globals.hpp"

// --------------------------------------------------
// HttpFetcher
// --------------------------------------------------
HttpFetcher::HttpFetcher ()
    : QObject ()
{
    connect (&_http, SIGNAL (done (bool)), SLOT (requestDone (bool)));
}


bool HttpFetcher::busy () const
{
    return _http.currentId () != 0;
}


void HttpFetcher::fetch (const QString& url)
{
    QUrl u (url);

    if (!CHECK_FOR_CONNECTION || ConnectionChecker::instance ()->isConnected ())
        if (u.isValid ()) {
            _http.setHost (u.host ());
            _http.get (u.encodedPath (), &_buffer);
        }
}


void HttpFetcher::requestDone (bool err)
{
    if (err)
        error (_http.error ());
    else
        done (_buffer.buffer ());
    _buffer.close ();
    _buffer.setBuffer (NULL);
}
