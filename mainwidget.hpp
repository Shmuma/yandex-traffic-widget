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

    // Other stuff
    QTimer *_timer;

public:
    MainWidget ();
    virtual ~MainWidget ();

public slots:
    void settingsDialog ();
    void updateData ();

protected:
    bool event (QEvent *event);
    void paintEvent (QPaintEvent *event);

    void updateSize ();
    void applySettings ();

protected slots:
    void trafficUpdated ();
    void deviceLockChanged (bool locked);
};

#endif /* __MAINWIDGET_H__ */
