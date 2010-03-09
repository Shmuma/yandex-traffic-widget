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
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.setBrush(QColor(0, 0, 0, 128));
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(rect(), 10, 10);
        p.end();

        QWidget::paintEvent(event);
    }
};

#endif /* __MAINWIDGET_H__ */
