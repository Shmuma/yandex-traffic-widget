#ifndef __TRAFFIC_H__
#define __TRAFFIC_H__

#include <QtCore>
#include <QtNetwork>


#include "http_fetcher.hpp"

// Base data of traffic information
class TrafficInfo
{
private:
    float _len1, _len2, _len;
    QDateTime _ts;
    QString _isotime;
    QString _localtime;

public:
    TrafficInfo ();
};


class ExtendedTrafficInfo : public TrafficInfo
{
public:
    enum light_color {
        Red,
        Yellow,
        Green
    };

private:
    float _level_raw;
    quint8 _level;
    light_color _color;
    quint8 _tend;
    QString _hint;

public:
    ExtendedTrafficInfo ();
};


class Traffic : public QObject
{
    Q_OBJECT

private:
    QDateTime _ts;

    QMap<QString, TrafficInfo> _info;
    QMap<QString, ExtendedTrafficInfo> _ext_info;

    HttpFetcher _fetcher;

private slots:
    void fetchDone (const QByteArray& data);

signals:
    void updated ();

public:
    Traffic ();

    void update ();
};


#endif // __TRAFFIC_H__
