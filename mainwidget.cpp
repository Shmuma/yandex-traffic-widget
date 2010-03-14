#include <QtGui>

#include "mainwidget.hpp"
#include "settingsDialog.hpp"


// --------------------------------------------------
// MainWidget
// --------------------------------------------------
MainWidget::MainWidget ()
    : QWidget ()
{
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_TranslucentBackground);
#endif
    _light = new TrafficLight (this);
    _label = new QLabel (this);

    _label->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

    _traffic = new Traffic;
    _regions = new RegionsTable;
    _settings = new Settings;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget (_light);
    layout->addWidget (_label);
    setLayout (layout);

    _light->setVisible (_settings->check (Settings::C_Light));

    updateSize ();

    connect (_traffic, SIGNAL (updated ()), SLOT (trafficUpdated ()));

    // every 5 minutes (TODO, make option)
    startTimer (5*60*1000);

    updateData ();
}


MainWidget::~MainWidget ()
{
    delete _traffic;
    delete _regions;
    delete _settings;

    delete _light;
    delete _label;
}


void MainWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setBrush (QColor(0, 0, 0, 128));
    p.setPen (Qt::NoPen);
    p.drawRoundedRect (rect(), 10, 10);
    p.end ();

    QWidget::paintEvent (event);
}


void MainWidget::timerEvent (QTimerEvent *)
{
    updateData ();
}



void MainWidget::trafficUpdated ()
{
    ExtendedTrafficInfo info = _traffic->lookup_ext ("1");

    if (info.valid ()) {
        QString data;
        bool first = true;
        _light->setColor (info.color ());

        if (_settings->check (Settings::C_Rank)) {
            data.append (QString::number (info.level ()));
            data.append (info.level () > 1 ? tr (" points") : tr (" point"));
            first = false;
        }

        if (_settings->check (Settings::C_Time)) {
            if (!first)
                data.append (", ");
            data.append (info.localtime ());
            first = false;
        }

        if (_settings->check (Settings::C_Hint)) {
            if (!first)
                data.append ("\n");
            data.append (info.hint ());
        }

        _label->setText (data);
    }
    else
        _light->setColor (ExtendedTrafficInfo::Unknown);
}


void MainWidget::updateData ()
{
    // Here we need to check for internet connection
    _traffic->update ();
}


void MainWidget::settingsDialog ()
{
    SettingsDialog dlg (_settings);

    dlg.exec ();

    // Handle settings
    _light->setVisible (_settings->check (Settings::C_Light));

    updateSize ();
    trafficUpdated ();
}


void MainWidget::updateSize ()
{
    QSize minSize (0, 80);

    if (_settings->check (Settings::C_Light))
        minSize += QSize (80, 0);
    if (_settings->check (Settings::C_Hint))
        minSize += QSize (270, 0);
    else {
        if (_settings->check (Settings::C_Time))
            minSize += QSize (75, 0);
        if (_settings->check (Settings::C_Rank))
            minSize += QSize (75, 0);
    }

    setFixedSize (minSize);
}
