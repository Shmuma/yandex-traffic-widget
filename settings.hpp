#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QtCore>


class Settings : public QObject
{
    Q_OBJECT
public:
    enum check_t {
        C_Light = 0,
        C_Rank,
        C_Time,
        C_Hint,
    };

private:
    QString _regionID;          // region ID which will be displayed
    QMap<QString, QString> _cities;
    QMap<check_t, bool> _checks;

    void makeDefault ();

    void loadCities (QSettings *settings);
    void saveCities (QSettings *settings);

public:
    Settings ();

    void load ();
    void save ();

    QString regionID () const
    { return _regionID; };

    QMap<QString, QString> cities () const
    { return _cities; };

    bool check (check_t entry) const
    { return _checks[entry]; };

    void setCheck (check_t entry, bool val)
    { _checks[entry] = val; }
};


#endif // __SETTINGS_H__
