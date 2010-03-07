TEMPLATE = app

SOURCES += qmaemo5homescreenadaptor.cpp
HEADERS += qmaemo5homescreenadaptor.h

SOURCES += main.cpp
HEADERS += mainwidget.hpp

desktop.path = /usr/share/applications/hildon-home
desktop.files = yandex-traffic-widget.desktop

target.path = /usr/lib/hildon-desktop
INSTALLS += target desktop
