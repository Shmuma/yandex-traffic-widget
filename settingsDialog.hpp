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
    QMaemo5ValueButton *displayButton;
    QMaemo5ValueButton *updateButton;
    QMaemo5ValueButton *alertsButton;

    Settings *_settings;

protected slots:
    void displayClicked ();

public:
    SettingsDialog (Settings *settings);
};


class DisplaySettingsDialog : public QDialog
{
    Q_OBJECT

private:
    Settings *_settings;
    QListWidget *_cities;
    QCheckBox *_showLight, *_showRank, *_showTime, *_showHint;
    QPushButton *_saveButton;

    void initCities (QBoxLayout *layout);
    void initChecks (QBoxLayout *layout);

public:
    DisplaySettingsDialog (Settings *settings);
};


#endif // __SETTINGSDIALOG_H__
