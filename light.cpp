#include <QtGui>
#include "light.hpp"
#include "traffic.hpp"


// --------------------------------------------------
// TrafficLight
// --------------------------------------------------
TrafficLight::TrafficLight (QWidget *parent)
    : QWidget (parent)
{
    _color = ExtendedTrafficInfo::Green;
}


void TrafficLight::paintEvent (QPaintEvent *)
{
    QPainter painter (this);
    QColor color;
    int side = qMin (width (), height ());

    switch (_color) {
        case ExtendedTrafficInfo::Green:
            color = Qt::green;
            break;
        case ExtendedTrafficInfo::Yellow:
            color = Qt::yellow;
            break;
        case ExtendedTrafficInfo::Red:
            color = Qt::red;
            break;
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen (color);
    painter.setBrush (color);
    painter.drawEllipse ((width ()-side)/2, (height ()-side)/2, side, side);
}

