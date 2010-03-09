#include <QtGui>

#include "mainwidget.hpp"



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

        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget (_light);
        layout->addWidget (_label);
        setLayout (layout);

        _label->setText ("Bla-bla");
}


QSize MainWidget::sizeHint() const
{
    return QWidget::sizeHint () + QSize (20, 0);
}
