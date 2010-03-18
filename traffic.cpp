#include <QtCore>
#include <QtXml>

#include "traffic.hpp"
#include "log.hpp"
#include "connection.hpp"


// --------------------------------------------------
// TrafficInfo
// --------------------------------------------------
TrafficInfo::TrafficInfo (const QDomElement& elem) throw (const QString&)
{
    _valid = false;
    _len1 = getFloatNode (elem, "length_1", 0);
    _len2 = getFloatNode (elem, "length_2", 0);
    _len  = getFloatNode (elem, "length", 0);
    _ts   = getTSNode (elem, "timestamp");
    _isotime = getStringNode (elem, "isotime");
    _localtime = getStringNode (elem, "localtime");
    _valid = true;
}


float TrafficInfo::getFloatNode (const QDomElement& elem, const char* node, float def)
{
    QDomElement e;
    bool ok;
    float val;

    e = elem.firstChildElement (node);
    if (e.isNull ())
        return def;
    val = e.text ().toFloat (&ok);
    if (!ok)
        return def;
    return val;
}


int TrafficInfo::getIntNode (const QDomElement& elem, const char* node, int def)
{
    QDomElement e;
    bool ok;
    int val;

    e = elem.firstChildElement (node);
    if (e.isNull ())
        return def;
    val = e.text ().toInt (&ok);
    if (!ok)
        return def;
    return val;
}


QString TrafficInfo::getStringNode (const QDomElement& elem, const char* node) throw (const QString&)
{
    QDomElement e;
    QString val;

    e = elem.firstChildElement (node);
    if (e.isNull ())
        throw QString (QString::fromAscii (node) + " not found");
    return e.text ();
}


QDateTime TrafficInfo::getTSNode (const QDomElement& elem, const char* node) throw (const QString&)
{
    QDomElement e;
    bool ok;
    uint val;
    QDateTime ts;

    e = elem.firstChildElement (node);
    if (e.isNull ())
        throw QString (QString::fromAscii (node) + " not found");
    val = e.text ().toUInt (&ok);
    if (!ok)
        throw QString (QString::fromAscii (node) + " is not a timestamp");
    ts.setTime_t (val);
    return ts;
}


void TrafficInfo::dump ()
{
    Log::instance ()->add (QString ("TrafficInfo (%1): time = %2").arg (_valid ? "valid" : "not valid").arg (_localtime));
}


// --------------------------------------------------
// ExtendedTrafficInfo
// --------------------------------------------------
ExtendedTrafficInfo::ExtendedTrafficInfo (const QDomElement& elem) throw (const QString&)
    : TrafficInfo (elem)
{
    QString color;

    setValid (false);
    _level_raw = getFloatNode (elem, "level_raw", 0);
    _level = getIntNode (elem, "level", 1);
    _tend = getIntNode (elem, "tend", 0);
    _hint = getStringNode (elem, "hint");

    color = getStringNode (elem, "icon");
    if (color == "green")
        _color = Green;
    else if (color == "yellow")
        _color = Yellow;
    else if (color == "red")
        _color = Red;
    else
        throw "Color is unknown";

    setValid (true);
}


void ExtendedTrafficInfo::dump ()
{
    TrafficInfo::dump ();
    Log::instance ()->add (QString ("ExtTrafficInfo: level = %1, hint = %2").arg (_level).arg (_hint));
}


// --------------------------------------------------
// Traffic
// --------------------------------------------------
Traffic::Traffic ()
    : QObject ()
{
    connect (&_fetcher, SIGNAL (done (const QByteArray&)),
             SLOT (fetchDone (const QByteArray&)));
    connect (ConnectionChecker::instance (), SIGNAL (connected (bool)), SLOT (connectionChanged (bool)));
}


// Perform asyncronous refresh of traffic information. If another update
// request is in progress, new is discarded. If update request finished
// successfully, updated() signal called.
void Traffic::update ()
{
    if (_fetcher.busy ()) {
        Log::instance ()->add ("Traffic::update: fetcher is busy");
        return;
    }

    Log::instance ()->add ("Traffic::update: Request status download");
    _fetcher.fetch ("http://trf.maps.yandex.net/trf/stat.xml");
}


void Traffic::fetchDone (const QByteArray& data)
{
    // parse data got
    if (parse_traffic_data (QString::fromUtf8 (data.data ()))) {
        Log::instance ()->add ("Traffic::fetchDone: data parsed successfully");
        updated ();
    }
    else
        Log::instance ()->add ("Traffic::fetchDone: data parse error");
}


bool Traffic::parse_traffic_data (const QString& xml)
{
    QDomDocument doc;
    QDateTime new_ts;
    QDomElement e;
    QDomNode n;
    bool ok;
    QString s;
    QMap<QString, TrafficInfo> new_info;
    QMap<QString, ExtendedTrafficInfo> new_ext_info;

    if (!doc.setContent (xml))
        return false;

    // get timestamp
    e = doc.documentElement ();
    if (e.isNull () || e.tagName () != "jams_stat")
        return false;

    s = e.attribute ("timestamp");
    if (s.isNull ())
        return false;

    new_ts.setTime_t (s.toUInt (&ok));
    if (!ok)
        return false;

    // parse all regions
    n = e.firstChild ();
    while (!n.isNull ()) {
        e = n.toElement ();
        if (!e.isNull () && e.tagName () == "region") {
            s = e.attribute ("id");
            try {
		// Check that it is an extended traffic info
                if (!e.firstChildElement ("level").isNull ()) {
                    ExtendedTrafficInfo info (e);
                    if (info.valid ())
                        new_ext_info[s] = info;
                }
                else {
                    TrafficInfo info (e);
                    if (info.valid ())
                        new_info[s] = info;
                }
            }
            catch (const QString& msg) {
            }
        }
        n = n.nextSibling ();
    }

    _ts = new_ts;
    _info = new_info;
    _ext_info = new_ext_info;

    return true;
}


TrafficInfo Traffic::lookup (const QString &id) const
{
    QMap<QString, TrafficInfo>::const_iterator it = _info.find (id);

    if (it == _info.end ())
        return TrafficInfo ();
    else
        return it.value ();
}


ExtendedTrafficInfo Traffic::lookup_ext (const QString &id) const
{
    QMap<QString, ExtendedTrafficInfo>::const_iterator it = _ext_info.find (id);

    if (it == _ext_info.end ())
        return ExtendedTrafficInfo ();
    else
        return it.value ();
}


void Traffic::connectionChanged (bool active)
{
    if (!active)
        _fetcher.reset ();
}
