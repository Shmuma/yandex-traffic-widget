#include <QtGui>
#include "light.hpp"
#include "traffic.hpp"


// --------------------------------------------------
// TrafficLight
// --------------------------------------------------
TrafficLight::TrafficLight (QWidget *parent)
    : QWidget (parent)
{
    _color = CityTrafficInfo::Unknown;
    setFixedSize (40, 40);
}


void TrafficLight::paintEvent (QPaintEvent *)
{
    QPainter painter (this);
    QColor color;
    int side = qMin (width (), height ());

    switch (_color) {
        case CityTrafficInfo::Unknown:
            color = Qt::gray;
            break;
        case CityTrafficInfo::Green:
            color = Qt::green;
            break;
        case CityTrafficInfo::Yellow:
            color = Qt::yellow;
            break;
        case CityTrafficInfo::Red:
            color = Qt::red;
            break;
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen (color);
    painter.setBrush (color);
    painter.drawEllipse ((width ()-side)/2, (height ()-side)/2, side, side);
}

