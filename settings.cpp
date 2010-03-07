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
    _regions.clear ();
    _regions.append ("1");      // Moscow
}
