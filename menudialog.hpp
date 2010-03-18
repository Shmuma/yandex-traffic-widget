#ifndef __MENUDIALOG_H__
#define __MENUDIALOG_H__

#include <QtGui>


class MenuDialog : public QDialog
{
    Q_OBJECT
private:
    QList<QPushButton*> _buttons;
    QBoxLayout* _layout;
    int index;

protected slots:
    void buttonClicked ();

public:
    MenuDialog (const QString &title);
    MenuDialog& addEntry (const QString &text);
    int run ();
};

#endif // __MENUDIALOG_H__
