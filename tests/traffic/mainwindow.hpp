#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>
#include <traffic.hpp>


class MainWindow : public QPushButton
{
    Q_OBJECT

private:
    Traffic _traffic;

protected slots:
    void fetchTraffic ()
    {
        printf ("Traffic update requested\n");
        _traffic.update ();
    }

    void trafficUpdated ()
    {
        ExtendedTrafficInfo info;

        printf ("Traffic data updated:\n");
        printf ("ts: %s\n", _traffic.ts ().toString ().toUtf8 ().data ());

        info = _traffic.lookup_ext ("1");
        printf ("Moscow: %d, %d, %s\n", info.level (), info.tend (), info.hint ().toUtf8 ().data ());
    }

public:
    MainWindow ()
        : QPushButton ()
    {
        connect (this, SIGNAL (clicked ()), this, SLOT (fetchTraffic ()));
        connect (&_traffic, SIGNAL (updated ()), this, SLOT (trafficUpdated ()));
        setText ("Fetch traffic information");
    }
};


#endif // __MAINWINDOW_H__
