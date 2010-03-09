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
        const RegionInfo *ri;

        setAlignment(Qt::AlignCenter);
#ifdef Q_WS_MAEMO_5
        setAttribute(Qt::WA_TranslucentBackground);
#endif
        ri = _regions.lookup (_settings.regions ()[0]);

        setText (_settings.regions ().join (", ") + ", " + QString (ri ? ri->name () : ""));
    }

    QSize sizeHint() const
    {
        return QLabel::sizeHint() + QSize (20, 0);
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.setBrush(QColor(0, 0, 0, 128));
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(rect(), 10, 10);
        p.end();

        QLabel::paintEvent(event);
    }
};

#endif /* __MAINWIDGET_H__ */
