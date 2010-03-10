#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>
#include <connection.hpp>

class MainWindow : public QPushButton
{
    Q_OBJECT
public:
    MainWindow ()
        : QPushButton ()
    {
        ConnectionChecker *cc = ConnectionChecker::instance ();

        connect (cc, SIGNAL (connected (bool)), SLOT (connected (bool)));

        setText (cc->isConnected () ? "Connected" : "Not connected");
        connect (this, SIGNAL (clicked ()), SLOT (checkConnection ()));
    }

protected slots:
    void connected (bool active)
    {
        if (active)
            printf ("Device connected\n");
        else
            printf ("Device not connected\n");
        setText (ConnectionChecker::instance ()->isConnected () ? "Connected" : "Not connected");
    }

    void checkConnection ()
    {
        ConnectionChecker::instance ()->requestState ();
    }
};

#endif // __MAINWINDOW_H__
