#include <QtCore>
#include <settings.hpp>


Settings::Settings ()
{
    if (!load ())
        makeDefault ();
}


bool Settings::load ()
{
    return false;
}


bool Settings::save ()
{
    return false;
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
