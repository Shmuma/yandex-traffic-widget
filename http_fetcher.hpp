#ifndef __HTTP_FETCHER_H__
#define __HTTP_FETCHER_H__

#include <QtCore>
#include <QtNetwork>


class HttpFetcher : public QObject
{
    Q_OBJECT
private:
    QHttp _http;
    QBuffer _buffer;

private slots:
    void requestDone (bool err);

signals:
    void error (QHttp::Error error);
    void done (const QByteArray& data);

public:
    HttpFetcher ();

    bool busy () const;
    void fetch (const QString& url);
    void reset ();
};


#endif // __HTTP_FETCHER_H__
