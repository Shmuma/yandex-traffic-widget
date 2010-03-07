#ifndef __SETTINGS_H__
#define __SETTINGS_H__



class Settings
{
private:
    QStringList _regions;       // List of regions IDs to display

    void makeDefault ();

public:
    Settings ();

    bool load ();
    bool save ();

    QStringList regions () const
    { return _regions; };
};


#endif // __SETTINGS_H__
