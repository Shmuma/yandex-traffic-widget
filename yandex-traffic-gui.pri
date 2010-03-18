HEADERS += $$PWD/mainwidget.hpp $$PWD/light.hpp $$PWD/settingsDialog.hpp $$PWD/menudialog.hpp
SOURCES += $$PWD/mainwidget.cpp $$PWD/light.cpp $$PWD/settingsDialog.cpp $$PWD/menudialog.cpp

!maemo5 {
        HEADERS += $$PWD/QtMaemo5Adapters.hpp
        SOURCES += $$PWD/QtMaemo5Adapters.cpp
}

QT += network xml

maemo5 {
       QT += maemo5
}

INCLUDEPATH += $$PWD
