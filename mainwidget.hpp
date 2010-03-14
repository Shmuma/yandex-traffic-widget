#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include <QtGui>

#include "traffic.hpp"
#include "settings.hpp"
#include "regions.hpp"
#include "light.hpp"


class MainWidget : public QWidget
{
    Q_OBJECT
private:
    Traffic* _traffic;
    RegionsTable* _regions;
    Settings* _settings;

    // Widgets
    TrafficLight* _light;
    QLabel* _label;

public:
    MainWidget ();
    virtual ~MainWidget ();

public slots:
    void settingsDialog ();

protected:
    void paintEvent (QPaintEvent *event);
    void timerEvent (QTimerEvent *event);

    void updateData ();
    void updateSize ();

protected slots:
    void trafficUpdated ();
};

#endif /* __MAINWIDGET_H__ */
