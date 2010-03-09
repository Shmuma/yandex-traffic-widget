#ifndef __TRAFFIC_H__
#define __TRAFFIC_H__

#include <QtCore>
#include <QtNetwork>
#include <QtXml>


#include "http_fetcher.hpp"

// Base data of traffic information
class TrafficInfo
{
private:
    float _len1, _len2, _len;
    QDateTime _ts;
    QString _isotime;
    QString _localtime;

    bool _valid;

protected:
    float getFloatNode (const QDomElement& elem, const char* node, float def);
    int getIntNode (const QDomElement& elem, const char* node, int def);
    QString getStringNode (const QDomElement& elem, const char* node) throw (const QString&);
    QDateTime getTSNode (const QDomElement& elem, const char* node) throw (const QString&);

    void setValid (bool new_val)
    { _valid = new_val; };

public:
    TrafficInfo ()
        : _valid (false)
    {};

    TrafficInfo (const QDomElement& elem) throw (const QString&);

    bool valid () const
    { return _valid; };
};


class ExtendedTrafficInfo : public TrafficInfo
{
public:
    enum light_color {
        Unknown,
        Red,
        Yellow,
        Green
    };

private:
    float _level_raw;
    int _level;
    light_color _color;
    int _tend;
    QString _hint;

public:
    ExtendedTrafficInfo ()
        : TrafficInfo ()
    {};

    ExtendedTrafficInfo (const QDomElement& elem) throw (const QString&);

    int level () const
    { return _level; };

    int tend () const
    { return _tend; };

    QString hint () const
    { return _hint; };
};


class Traffic : public QObject
{
    Q_OBJECT

private:
    QDateTime _ts;

    QMap<QString, TrafficInfo> _info;
    QMap<QString, ExtendedTrafficInfo> _ext_info;

    HttpFetcher _fetcher;

    bool parse_traffic_data (const QString& xml);

private slots:
    void fetchDone (const QByteArray& data);

signals:
    void updated ();

public:
    Traffic ();

    void update ();

    QDateTime ts () const
    { return _ts; };

    TrafficInfo lookup (const QString &id) const;
    ExtendedTrafficInfo lookup_ext (const QString &id) const;
};


#endif // __TRAFFIC_H__
