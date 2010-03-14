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

    _checks[C_Light] = settings.value ("checks/light", _checks[C_Light]).toBool ();
    _checks[C_Rank] = settings.value ("checks/rank", _checks[C_Rank]).toBool ();
    _checks[C_Time] = settings.value ("checks/time", _checks[C_Time]).toBool ();
    _checks[C_Hint] = settings.value ("checks/hint", _checks[C_Hint]).toBool ();

    loadCities (&settings);
}


void Settings::save ()
{
    QSettings settings;

    settings.setValue ("region", _regionID);

    settings.setValue ("checks/light", _checks[C_Light]);
    settings.setValue ("checks/rank", _checks[C_Rank]);
    settings.setValue ("checks/time", _checks[C_Time]);
    settings.setValue ("checks/hint", _checks[C_Hint]);

    saveCities (&settings);
}


void Settings::loadCities (QSettings *settings)
{
    QMap<QString, QVariant> v;
    QMap<QString, QVariant>::const_iterator it;

    v = settings->value ("cities", v).toMap ();

    if (v.size () == 0)
        return;

    it = v.begin ();
    _cities.clear ();

    while (it != v.end ()) {
        _cities[it.key ()] = it.value ().toString ();
        it++;
    }
}


void Settings::saveCities (QSettings *settings)
{
    QMap<QString, QVariant> v;
    QMap<QString, QString>::const_iterator it;

    it = _cities.begin ();

    while (it != _cities.end ()) {
        v[it.key ()] = it.value ();
        it++;
    }

    settings->setValue ("cities", v);
}


void Settings::makeDefault ()
{
    _regionID = "1";            // Default city

    _cities["1"] = tr ("Moscow");
    _cities["10174"] = tr ("Kiev");
    _cities["11162"] = tr ("Ekaterinburg");
    _cities["11079"] = tr ("N.Novgorod");

    setCheck (C_Light, true);
    setCheck (C_Rank, true);
    setCheck (C_Hint, true);
}
