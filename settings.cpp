#include <QtCore>
#include <settings.hpp>


Settings::Settings ()
{
    load ();
}


void Settings::load ()
{
    QSettings settings;

    makeDefault ();

    _regionID = settings.value ("region", _regionID).toString ();

    _checks[C_ShowLight] = settings.value ("checks/light", _checks[C_ShowLight]).toBool ();
    _checks[C_ShowRank] = settings.value ("checks/rank", _checks[C_ShowRank]).toBool ();
    _checks[C_ShowTime] = settings.value ("checks/time", _checks[C_ShowTime]).toBool ();
    _checks[C_ShowHint] = settings.value ("checks/hint", _checks[C_ShowHint]).toBool ();
    _checks[C_UpdateOnWiFi] = settings.value ("checks/updateOnWifi", _checks[C_UpdateOnWiFi]).toBool ();
    _checks[C_UpdateOnGSM] = settings.value ("checks/updateOnGSM", _checks[C_UpdateOnGSM]).toBool ();
    _checks[C_UpdateWhenLocked] = settings.value ("checks/updateWhenLocked", _checks[C_UpdateWhenLocked]).toBool ();

    _updateIntervalIndex = minutes2IntervalIndex (settings.value ("updateInterval", intervalIndex2Minutes (_updateIntervalIndex)).toInt ());

    _langIndex = settings.value ("langIndex", _langIndex).toInt ();
    if (_langIndex < 0 || _langIndex >= _langs.count ())
        _langIndex = 0;
}


void Settings::save ()
{
    QSettings settings;

    settings.setValue ("region", _regionID);

    settings.setValue ("checks/light", _checks[C_ShowLight]);
    settings.setValue ("checks/rank", _checks[C_ShowRank]);
    settings.setValue ("checks/time", _checks[C_ShowTime]);
    settings.setValue ("checks/hint", _checks[C_ShowHint]);
    settings.setValue ("checks/updateOnWifi", _checks[C_UpdateOnWiFi]);
    settings.setValue ("checks/updateOnGSM", _checks[C_UpdateOnGSM]);
    settings.setValue ("checks/updateWhenLocked", _checks[C_UpdateWhenLocked]);

    settings.setValue ("updateInterval", intervalIndex2Minutes (_updateIntervalIndex));

    settings.setValue ("langIndex", _langIndex);
}


void Settings::makeDefault ()
{
    _regionID = "1";            // Default city

    _cities["1"] = tr ("Moscow");
    _cities["10174"] = tr ("St.Petersburg");
    _cities["20544"] = tr ("Kiev");
    _cities["11162"] = tr ("Ekaterinburg");

    setCheck (C_ShowLight, true);
    setCheck (C_ShowRank, true);
    setCheck (C_ShowHint, true);

    setCheck (C_UpdateOnWiFi, true);

    setCheck (C_UpdateWhenLocked, true);

    _updateIntervalIndex = 3;

    // languages
    _langIndex = 0;
    _langs.append (Language (QString (""),   tr ("System")));
    _langs.append (Language (QString ("en"), tr ("English")));
    _langs.append (Language (QString ("ru"), tr ("Russian")));
}


QStringList Settings::updateIntervals () const
{
    QStringList res;

    res.append (tr ("Never"));
    res.append (tr ("1 min"));
    res.append (tr ("2 min"));
    res.append (tr ("5 min"));
    res.append (tr ("15 min"));
    res.append (tr ("30 min"));

    return res;
}


int Settings::intervalIndex2Minutes (int index) const
{
    int int2min[] = { -1, 1, 2, 5, 15, 30 };

    if (index < 0 || sizeof (int2min) / sizeof (int2min[0]) <= (unsigned int)index)
        return -1;

    return int2min[index];
}


int Settings::minutes2IntervalIndex (int minutes) const
{
    switch (minutes) {
        case -1:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 5:
            return 3;
        case 15:
            return 4;
        case 30:
            return 5;
        default:
            return 0;
    }
}
