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
        setAttribute(Qt::WA_TranslucentBackground);

        ri = _regions.lookup (_settings.regions ()[0]);

        setText (_settings.regions ().join (", ") + ", " + QString (ri ? ri->name () : ""));
    }

    QSize sizeHint() const
    {
        return 2 * QLabel::sizeHint();
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.setBrush(QColor(0, 0, 0, 128));
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(rect(), 25, 25);
        p.end();

        QLabel::paintEvent(event);
    }
};

#endif /* __MAINWIDGET_H__ */
