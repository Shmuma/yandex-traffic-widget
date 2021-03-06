#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <QtCore>



class Language
{
private:
    QString _title;
    QString _alias;

public:
    Language (const QString &alias, const QString &title)
        : _title (title),
          _alias (alias)
    {};

    QString title () const;

    QString alias () const
    { return _alias; };

    bool operator== (const Language &lang) const
    { return _title == lang._title && _alias == lang._alias; };

    bool operator!= (const Language &lang) const
    { return !(*this == lang); };
};


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
        C_UpdateWhenLocked,
    };

private:
    QString _regionID;          // region ID which will be displayed
    QMap<QString, QString> _cities;
    QMap<check_t, bool> _checks;
    int _updateIntervalIndex;

    QList<Language> _langs;
    int _langIndex;

    QTranslator *_ts;

    void makeDefault ();

    int intervalIndex2Minutes (int index) const;
    int minutes2IntervalIndex (int minutes) const;

    Settings ();

    void refreshTranslations ();

public:
    static Settings* instance ();

    void load ();
    void save ();

    QString regionID () const
    { return _regionID; };

    void setRegionID (const QString &id)
    { _regionID = id; };

    QStringList regionIDs () const
    { return _cities.keys (); };

    QString regionName (const QString &id) const;

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

    // Language settings
    const Language& language () const
    { return _langs[_langIndex]; };

    const QList<Language>& languages () const
    { return _langs; };

    void setLanguageIndex (int index);

signals:
    void translationsUpdated ();
};


#endif // __SETTINGS_H__
