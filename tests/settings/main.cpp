#include <QtGui>

#include "settings.hpp"
#include "settingsDialog.hpp"

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    Settings settings;
    SettingsDialog dlg (&settings);

    dlg.show ();

    return app.exec ();
}
