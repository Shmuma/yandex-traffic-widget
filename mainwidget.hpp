#ifndef __MAINWIDGET_H__
#define __MAINWIDGET_H__

#include <QtGui>

#include <settings.hpp>
#include <regions.hpp>


class MainWidget : public QLabel
{
    Q_OBJECT
private:
    RegionsTable _regions;
    Settings _settings;

public:
    MainWidget ()
        : QLabel ()
    {
        setAlignment(Qt::AlignCenter);
        setAttribute(Qt::WA_TranslucentBackground);

        setText (_settings.regions ().join (", "));
    }

    QSize sizeHint() const
    {
        return 2 * QLabel::sizeHint();
    }
};

#endif /* __MAINWIDGET_H__ */
