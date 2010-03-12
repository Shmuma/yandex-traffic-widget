HEADERS += $$PWD/mainwidget.hpp $$PWD/light.hpp $$PWD/settingsDialog.hpp
SOURCES += $$PWD/mainwidget.cpp $$PWD/light.cpp $$PWD/settingsDialog.cpp

!maemo5 {
        HEADERS += $$PWD/QtMaemo5Adapters.hpp
        SOURCES += $$PWD/QtMaemo5Adapters.cpp
}

QT += network xml

maemo5 {
       QT += maemo5
}

INCLUDEPATH += $$PWD
