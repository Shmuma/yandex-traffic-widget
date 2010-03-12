#ifndef __QTMaemo5ADAPTERS_H__
#define __QTMaemo5ADAPTERS_H__

#include <QtGui>


class QMaemo5ValueButton : public QPushButton
{
    Q_OBJECT
private:
public:
    QMaemo5ValueButton (const QString& text, QWidget *parent);
};


#endif // __QTMaemo5ADAPTERS_H__
