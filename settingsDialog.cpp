#include <QtGui>
#include "settingsDialog.hpp"


// --------------------------------------------------
// SettingsDialog
// --------------------------------------------------
SettingsDialog::SettingsDialog (QWidget *parent, Settings *settings)
    : QDialog (parent)
{
    setWindowTitle (tr ("Settings"));
}
