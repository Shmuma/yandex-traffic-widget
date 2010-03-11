#ifndef __SETTINGSDIALOG_H__
#define __SETTINGSDIALOG_H__

#include <QtGui>

#include "settings.hpp"


class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog (QWidget *parent, Settings *settings);
};


#endif // __SETTINGSDIALOG_H__
