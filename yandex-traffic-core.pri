HEADERS += $$PWD/regions.hpp $$PWD/settings.hpp $$PWD/traffic.hpp $$PWD/http_fetcher.hpp $$PWD/connection.hpp
SOURCES += $$PWD/regions.cpp $$PWD/settings.cpp $$PWD/traffic.cpp $$PWD/http_fetcher.cpp $$PWD/connection.cpp

HEADERS += $$PWD/icd2_light.h $$PWD/globals.hpp

QT += network xml dbus
CONFIG += qdbus 

maemo5 {
       CONFIG += icd2
}

INCLUDEPATH += $$PWD
