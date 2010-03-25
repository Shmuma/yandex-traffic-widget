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
    bool _valid;

protected:
    void setValid (bool new_val)
    { _valid = new_val; };

public:
    TrafficInfo ()
        : _valid (false)
    {};

    bool valid () const
    { return _valid; };
};


class CityTrafficInfo : public TrafficInfo
{
public:
    enum light_color {
        Unknown,
        Red,
        Yellow,
        Green
    };

private:
    QDateTime _ts;
    int _level, _tend;
    light_color _color;
    QString _hint;

    float getFloatNode (const QDomElement& elem, const char* node, float def);
    int getIntNode (const QDomElement& elem, const char* node, int def);
    QString getStringNode (const QDomElement& elem, const char* node) throw (const QString&);
    QDateTime getTSNode (const QDomElement& elem, const char* node) throw (const QString&);

public:
    CityTrafficInfo ()
        : TrafficInfo ()
    {};

    CityTrafficInfo (const QDomElement& elem) throw (const QString&);

    QDateTime ts () const
    { return _ts; };

    int level () const
    { return _level; };

    int tend () const
    { return _tend; };

    QString hint () const
    { return _hint; };

    CityTrafficInfo::light_color color () const
    { return _color; };

    virtual void dump ();
};


class Traffic : public QObject
{
    Q_OBJECT

private:
    QDateTime _ts;

    QMap<QString, CityTrafficInfo> _ext_info;

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

    CityTrafficInfo lookup_ext (const QString &id) const;
};


#endif // __TRAFFIC_H__
