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
        connect (cc, SIGNAL (type_changed (ConnectionChecker::network_type_t)), SLOT (type_changed (ConnectionChecker::network_type_t)));

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

    void type_changed (ConnectionChecker::network_type_t type)
    {
        switch (type) {
            case ConnectionChecker::Net_None:
                printf ("Type: none\n");
                break;
            case ConnectionChecker::Net_WLAN:
                printf ("Type: WLAN\n");
                break;
            case ConnectionChecker::Net_GSM:
                printf ("Type: GSM\n");
                break;
        }
    }

    void checkConnection ()
    {
        ConnectionChecker::instance ()->requestState ();
    }
};

#endif // __MAINWINDOW_H__
