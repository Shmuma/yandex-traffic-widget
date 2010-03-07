#include <QtCore>

#include "regions.hpp"


RegionsTable::RegionsTable ()
{
    // Load saved table, if failed, initialize default table of regions
    makeDefaultTable ();
}


void RegionsTable::makeDefaultTable ()
{
    _map.clear ();
    _map.insert ("1", RegionInfo ("1", "Moscow"));
    _map.insert ("10174", RegionInfo ("10174", "St. Petersburg"));
    _map.insert ("20544", RegionInfo ("20544", "Kiev"));
    _map.insert ("11162", RegionInfo ("11162", "Ekaterinburg"));
}


const RegionInfo *RegionsTable::lookup (const QString &id) const
{
    QMap<QString, RegionInfo>::const_iterator it = _map.find (id);

    if (it == _map.end ())
        return NULL;
    else
        return &*it;
}
