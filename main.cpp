#include <QtCore>
#include "qmaemo5homescreenadaptor.h"
#include "mainwidget.hpp"


int main(int argc, char *argv[])
{
    QApplication::setGraphicsSystem ("native");
    QApplication::setOrganizationName ("Shmuma");
    QApplication::setApplicationName ("yandex-traffic-widget");

    QApplication app (argc, argv);

    MainWidget w;
    QMaemo5HomescreenAdaptor *adaptor = new QMaemo5HomescreenAdaptor (&w);

    w.connect (adaptor, SIGNAL (settingsRequested ()), SLOT (settingsDialog ()));

    adaptor->setSettingsAvailable (true);

    w.show ();

    return app.exec ();
}

