#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QtGui>
#include <connection.hpp>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow ()
        : QWidget ()
    {
        ConnectionChecker *cc = ConnectionChecker::instance ();

        connect (cc, SIGNAL (connected (bool)), SLOT (connected (bool)));
    }

protected slots:
    void connected (bool active)
    {
        if (active)
            printf ("Device connected\n");
        else
            printf ("Device not connected\n");
    }
};

#endif // __MAINWINDOW_H__
