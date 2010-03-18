#include <QtGui>

#include "globals.hpp"
#include "mainwidget.hpp"
#include "settingsDialog.hpp"
#include "connection.hpp"
#include "devstate.hpp"
#include "settings.hpp"
#include "log.hpp"
#include "menudialog.hpp"


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
    _settings = Settings::instance ();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget (_light);
    layout->addWidget (_label);
    setLayout (layout);

    applySettings ();

    connect (_traffic, SIGNAL (updated ()), SLOT (trafficUpdated ()));
    connect (_timer, SIGNAL (timeout ()), SLOT (updateData ()));
    connect (DeviceState::instance (), SIGNAL (lockChanged (bool)), SLOT (deviceLockChanged (bool)));

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
        Log::instance ()->add ("trafficUpdated, info valid");
        info.dump ();
        _light->setColor (info.color ());

        if (_settings->check (Settings::C_ShowRank)) {
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
        Log::instance ()->add ("trafficUpdated, but info not valid");
        _light->setColor (ExtendedTrafficInfo::Unknown);
        _label->setText (tr ("No data"));
    }
}


void MainWidget::updateData ()
{
    bool update = true;

    Log::instance ()->add ("updateData called");

#if CHECK_FOR_CONNECTION
    update = ConnectionChecker::instance ()->checkConnection (_settings->check (Settings::C_UpdateOnGSM),
                                                              _settings->check (Settings::C_UpdateOnWiFi));
    Log::instance ()->add (QString ("checkConnection returned %1").arg (update ? "true" : "false"));
    if (!_settings->check (Settings::C_UpdateWhenLocked)) {
        Log::instance ()->add ("Check for device state");
        update &= !DeviceState::instance ()->locked ();
    }
#endif

    if (update) {
        Log::instance ()->add ("Perform update");
        _traffic->update ();
    }
    else
        Log::instance ()->add ("Update not performed");
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

    Log::instance ()->add (QString ("applySettings: updateInterval is %1").arg (_settings->updateInterval ()));

    if (_settings->updateInterval () < 0) {
        _timer->stop ();
        Log::instance ()->add ("Timer disabled");
    }
    else {
        _timer->setInterval (1000 * 60 * _settings->updateInterval ());
        _timer->start ();
        Log::instance ()->add (QString ("Timer interval set to %1 ms").arg (1000 * 60 * _settings->updateInterval ()));
    }
}


bool MainWidget::event (QEvent *event)
{
    if (event->type () != QEvent::WindowActivate)
        return QWidget::event (event);

    MenuDialog menu (tr ("Yandex.Traffic"));

    menu.addEntry (tr ("Settings")).addEntry (tr ("Update"));

    switch (menu.run ()) {
        case 0:
            settingsDialog ();
            break;
        case 1:
            _traffic->update ();
            break;
    }

    return QWidget::event (event);
}


void MainWidget::deviceLockChanged (bool locked)
{
    if (!_settings->check (Settings::C_UpdateWhenLocked))
        if (!locked)
            updateData ();
}
