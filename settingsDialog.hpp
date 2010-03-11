#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include <QtGui>
#include <QtMaemo5>

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
