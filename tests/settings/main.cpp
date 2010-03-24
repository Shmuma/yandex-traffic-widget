#include <QtGui>

#include "settings.hpp"
#include "settingsDialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    SettingsDialog dlg (Settings::instance ());

    dlg.show ();

    return app.exec ();
}
