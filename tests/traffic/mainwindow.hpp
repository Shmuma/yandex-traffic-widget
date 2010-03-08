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
        printf ("Clicked\n");
    }

public:
    MainWindow ()
        : QPushButton ()
    {
        connect (this, SIGNAL (clicked ()), this, SLOT (fetchTraffic ()));
        setText ("Push me");
    }
};


#endif // __MAINWINDOW_H__
