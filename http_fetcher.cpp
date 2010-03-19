#include <QtCore>
#include <QtNetwork>

#include "http_fetcher.hpp"

// --------------------------------------------------
// HttpFetcher
// --------------------------------------------------
HttpFetcher::HttpFetcher ()
    : QObject ()
{
    connect (&_http, SIGNAL (done (bool)), SLOT (requestDone (bool)));
}


void HttpFetcher::fetch (const QString& url)
{
    QUrl u (url);

    if (_http.currentId () != 0)
        _http.abort ();

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

