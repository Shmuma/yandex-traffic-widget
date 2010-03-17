#include <QtGui>

#include "mainwidget.hpp"
#include "settingsDialog.hpp"
#include "connection.hpp"


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
    _timer = new QTimer (this);

    _label->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);

    _traffic = new Traffic;
    _regions = new RegionsTable;
    _settings = new Settings;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget (_light);
    layout->addWidget (_label);
    setLayout (layout);

    applySettings ();

    connect (_traffic, SIGNAL (updated ()), SLOT (trafficUpdated ()));
    connect (_timer, SIGNAL (timeout ()), SLOT (updateData ()));

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



void MainWidget::trafficUpdated ()
{
    ExtendedTrafficInfo info = _traffic->lookup_ext (_settings->regionID ());

    if (info.valid ()) {
        QString data;
        bool first = true;
        _light->setColor (info.color ());

        if (_settings->check (Settings::C_ShowRank)) {
            data.append (QString::number (info.level ()));
            data.append (tr ("%n point(s)", "", info.level ()));
            first = false;
        }

        if (_settings->check (Settings::C_ShowTime)) {
            if (!first)
                data.append (", ");
            data.append (info.localtime ());
            first = false;
        }

        if (_settings->check (Settings::C_ShowHint)) {
            if (!first)
                data.append ("\n");
            data.append (info.hint ());
        }

        _label->setText (data);
    }
    else {
        _light->setColor (ExtendedTrafficInfo::Unknown);
        _label->setText (tr ("No data"));
    }
}


void MainWidget::updateData ()
{
    bool update = true;

#if CHECK_FOR_CONNECTION
    update = ConnectionChecker::instance ()->checkConnection (_settings->check (Settings::C_UpdateOnGSM),
                                                              _settings->check (Settings::C_UpdateOnWiFi));
    if (!_settings->check (Settings::C_UpdateWhenLocked))
        update &= !DeviceState::instance ()->locked ();
#endif

    if (update)
        _traffic->update ();
}


void MainWidget::settingsDialog ()
{
    SettingsDialog dlg (_settings);

    dlg.exec ();

    applySettings ();
    trafficUpdated ();
}


void MainWidget::updateSize ()
{
    QSize minSize (0, 80);

    if (_settings->check (Settings::C_ShowLight))
        minSize += QSize (80, 0);
    if (_settings->check (Settings::C_ShowHint))
        minSize += QSize (270, 0);
    else {
        if (_settings->check (Settings::C_ShowTime))
            minSize += QSize (75, 0);
        if (_settings->check (Settings::C_ShowRank))
            minSize += QSize (75, 0);
    }

    setFixedSize (minSize);
}



void MainWidget::applySettings ()
{
    _light->setVisible (_settings->check (Settings::C_ShowLight));

    updateSize ();

    if (_settings->updateInterval () < 0)
        _timer->stop ();
    else
        _timer->setInterval (1000 * 60 * _settings->updateInterval ());
}


void MainWidget::mousePressEvent (QMouseEvent *event)
{
    QMenu menu;
    QAction *settingsAction, *updateAction, *todo;

    settingsAction = menu.addAction (tr ("Settings"));
    updateAction = menu.addAction (tr ("Update"));

    todo = menu.exec (event->pos ());
    if (!todo)
        return;

    if (todo == settingsAction)
        settingsDialog ();
    if (todo == updateAction)
        _traffic->update ();
}
