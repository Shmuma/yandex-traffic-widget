#ifndef __QTMaemo5ADAPTERS_H__
#define __QTMaemo5ADAPTERS_H__

#include <QtGui>


class QMaemo5ValueButton : public QPushButton
{
    Q_OBJECT
public:
    enum Layout {
        ValueUnderText,
    };
private:
public:
    QMaemo5ValueButton (const QString& text, QWidget *parent);

    void setValueLayout (Layout)
    {};

    void setValueText (const QString &)
    {};
};


#endif // __QTMaemo5ADAPTERS_H__
