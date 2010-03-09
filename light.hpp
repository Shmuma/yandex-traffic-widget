#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <QtGui>

#include "traffic.hpp"

class TrafficLight : public QWidget
{
    Q_OBJECT

private:
    ExtendedTrafficInfo::light_color _color;

protected:
    void paintEvent (QPaintEvent *event);

public:
    TrafficLight (QWidget *parent);

    ExtendedTrafficInfo::light_color color () const
    { return _color; };

    void setColor (ExtendedTrafficInfo::light_color color)
    { 
        _color = color;
        update ();
    }
};

#endif // __LIGHT_H__
