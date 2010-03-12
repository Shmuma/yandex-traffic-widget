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
        C_TotalCount
    };

private:
    QString _regionID;          // region ID which will be displayed
    QMap<QString, QString> _cities;
    bool _checks[C_TotalCount];

    void makeDefault ();

public:
    Settings ();

    bool load ();
    bool save ();

    QString regionID () const
    { return _regionID; };

    QMap<QString, QString> cities () const
    { return _cities; };

    bool check (check_t entry) const
    { return _checks[entry]; };
};


#endif // __SETTINGS_H__
