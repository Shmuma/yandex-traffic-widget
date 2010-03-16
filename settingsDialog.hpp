#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include <QtGui>

#ifdef Q_WS_MAEMO_5
#include <QtMaemo5>
#else
#include "QtMaemo5Adapters.hpp"
#endif

#include "settings.hpp"


class SettingsDialog : public QDialog
{
    Q_OBJECT

private:
    QMaemo5ValueButton *_displayButton;
    QMaemo5ValueButton *_updateButton;

    Settings *_settings;

    void updateDisplayButtonValue ();
    void updateUpdateButtonValue ();

protected slots:
    void displayClicked ();
    void updateClicked ();

public:
    SettingsDialog (Settings *settings);
};


class BaseSettingsDialog : public QDialog
{
    Q_OBJECT
private:
    Settings *_settings;
    QVBoxLayout *_layout;
    QPushButton *_saveButton;

protected slots:
    void saveClicked ();

protected:
    Settings* settings () const
    { return _settings; };

    QVBoxLayout* layout () const
    { return _layout; };

    virtual void saveSettings () = 0;

public:
    BaseSettingsDialog (Settings *settings);
};


class DisplaySettingsDialog : public BaseSettingsDialog
{
    Q_OBJECT

private:
    QListWidget *_cities;
    QCheckBox *_showLight, *_showRank, *_showTime, *_showHint;

    void initCities (QBoxLayout *layout);
    void initChecks (QBoxLayout *layout);

protected:
    virtual void saveSettings ();

public:
    DisplaySettingsDialog (Settings *settings);
};


class UpdateSettingsDialog : public BaseSettingsDialog
{
    Q_OBJECT

private:
    QMaemo5ValueButton *_intervalButton;
    QCheckBox *_wifiUpdate, *_gsmUpdate, *_lockedUpdate;

    void initUpdateInterval (QBoxLayout *layout);

protected:
    virtual void saveSettings ();

public:
    UpdateSettingsDialog (Settings *settings);
};


#endif // __SETTINGSDIALOG_H__
