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

public:
    SettingsDialog (Settings *settings);
};


#endif // __SETTINGSDIALOG_H__
