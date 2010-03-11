#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>

#include "devstate.hpp"

class MainWindow : public QPushButton
{
    Q_OBJECT

protected slots:
    void clicked ()
    {
        printf ("Clicked, request state\n");
        DeviceState::instance ()->requestState ();
    }

    void lockChanged (bool state)
    {
        printf (state ? "device locked\n" : "device unlocked\n");
    }

public:
    MainWindow ()
        : QPushButton ()
    {
        setText ("Push me to get state");
        connect (this, SIGNAL (clicked ()), this, SLOT (clicked ()));
        connect (DeviceState::instance (), SIGNAL (lockChanged (bool)), this, SLOT (lockChanged (bool)));
    }
};

#endif // __MAINWINDOW_H__
