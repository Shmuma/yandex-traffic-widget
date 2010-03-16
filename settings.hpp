#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QtCore>


class Settings : public QObject
{
    Q_OBJECT
public:
    enum check_t {
        C_ShowLight = 0,
        C_ShowRank,
        C_ShowTime,
        C_ShowHint,
        C_UpdateOnWiFi,
        C_UpdateOnGSM,
    };

private:
    QString _regionID;          // region ID which will be displayed
    QMap<QString, QString> _cities;
    QMap<check_t, bool> _checks;
    int _updateIntervalIndex;

    void makeDefault ();

    void loadCities (QSettings *settings);
    void saveCities (QSettings *settings);

    int intervalIndex2Minutes (int index) const;
    int minutes2IntervalIndex (int minutes) const;

public:
    Settings ();

    void load ();
    void save ();

    QString regionID () const
    { return _regionID; };

    void setRegionID (const QString &id)
    { _regionID = id; };

    QMap<QString, QString> cities () const
    { return _cities; };

    bool check (check_t entry) const
    { return _checks[entry]; };

    void setCheck (check_t entry, bool val)
    { _checks[entry] = val; };

    QStringList updateIntervals () const;

    int getUpdateIntervalIndex () const
    { return _updateIntervalIndex; };

    void setUpdateIntervalIndex (int index)
    { _updateIntervalIndex = index; };

    int updateInterval () const
    { return intervalIndex2Minutes (_updateIntervalIndex); };
};


#endif // __SETTINGS_H__
