#include <QtGui>

#ifdef Q_WS_MAEMO_5
#include <QtMaemo5>
#else
#include "QtMaemo5Adapters.hpp"
#endif

#include "settingsDialog.hpp"


// --------------------------------------------------
// SettingsDialog
// --------------------------------------------------
SettingsDialog::SettingsDialog (Settings *settings)
    : QDialog ()
{
    setWindowTitle (tr ("Settings"));

    QVBoxLayout *layout = new QVBoxLayout (this);

    displayButton = new QMaemo5ValueButton (tr ("Display"), this);
    layout->addWidget (displayButton);
    updateButton = new QMaemo5ValueButton (tr ("Update"), this);
    layout->addWidget (updateButton);
    alertsButton = new QMaemo5ValueButton (tr ("Alerts"), this);
    layout->addWidget (alertsButton);
}
