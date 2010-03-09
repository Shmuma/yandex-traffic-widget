TEMPLATE = app

SOURCES += qmaemo5homescreenadaptor.cpp
HEADERS += qmaemo5homescreenadaptor.h

SOURCES += main.cpp
HEADERS +=

include (yandex-traffic-core.pri)
include (yandex-traffic-gui.pri)

desktop.path = /usr/share/applications/hildon-home
desktop.files = yandex-traffic-widget.desktop

target.path = /usr/lib/hildon-desktop
INSTALLS += target desktop
