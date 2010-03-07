#ifndef __REGIONS_H__
#define __REGIONS_H__

#include <QtCore>


class RegionInfo
{
private:
    QString _id;
    QString _name;

public:
    RegionInfo (const QString &id, const QString &name)
        : _id (id),
          _name (name)
    {};

    QString id () const
    { return _id; };

    QString name () const
    { return _name; };
};


// Map between region ID and it's information
class RegionsTable
{
private:
    QMap<QString, RegionInfo> _map;

    void makeDefaultTable ();

public:
    RegionsTable ();

    const RegionInfo *lookup (const QString &id) const;
};

#endif // __REGIONS_H__
