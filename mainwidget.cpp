#include <QtGui>

#include "mainwidget.hpp"



// --------------------------------------------------
// MainWidget
// --------------------------------------------------
MainWidget::MainWidget ()
    : QWidget ()
{
    setMinimumSize (300, 80);
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_TranslucentBackground);
#endif
    _light = new TrafficLight (this);
    _label = new QLabel (this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget (_light);
    layout->addWidget (_label);
    setLayout (layout);

    connect (&_traffic, SIGNAL (updated ()), SLOT (trafficUpdated ()));

    // every 5 minutes (TODO, make option)
    startTimer (5*60*1000);

    // perform update just after creation
    _traffic.update ();
}



void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush(QColor(0, 0, 0, 128));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), 10, 10);
    p.end();

    QWidget::paintEvent(event);
}


void MainWidget::timerEvent (QTimerEvent *)
{
    // Perform traffic information refresh
    // TODO: only if internet connection is available
    _traffic.update ();
}



void MainWidget::trafficUpdated ()
{
    ExtendedTrafficInfo info = _traffic.lookup_ext ("1");

    if (info.valid ()) {
        _light->setColor (info.color ());
        _label->setText (QString ("%1, %2\n%3")
                         .arg (QString::number (info.level ()))
                         .arg (info.localtime ())
                         .arg (info.hint ()));
    }
    else
        _light->setColor (ExtendedTrafficInfo::Unknown);
}
