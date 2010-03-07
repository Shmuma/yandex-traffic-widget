#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include <QtGui>

class MainWidget : public QLabel
{
    Q_OBJECT
public:
    MainWidget ()
        : QLabel (tr ("Hello, World"))
    {
        setAlignment(Qt::AlignCenter);
        setAttribute(Qt::WA_TranslucentBackground);
    }

    QSize sizeHint() const
    {
        return 2 * QLabel::sizeHint();
    }
};

#endif /* __MAINWIDGET_H__ */
