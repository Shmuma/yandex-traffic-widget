#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include <QtGui>

#include "settings.hpp"
#include "regions.hpp"
#include "light.hpp"


class MainWidget : public QWidget
{
    Q_OBJECT
private:
    RegionsTable _regions;
    Settings _settings;

    // Widgets
    TrafficLight *_light;
    QLabel *_label;

public:
    MainWidget ();
    QSize sizeHint () const;

protected:
    void paintEvent (QPaintEvent *event);
};

#endif /* __MAINWIDGET_H__ */
