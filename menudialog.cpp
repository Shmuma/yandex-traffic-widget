#include <QtGui>

#include "menudialog.hpp"


// --------------------------------------------------
// MenuDialog
// --------------------------------------------------
MenuDialog::MenuDialog (const QString &title)
    : QDialog ()
{
    setWindowTitle (title);
    _layout = new QVBoxLayout (this);
}


MenuDialog& MenuDialog::addEntry (const QString &text)
{
    QPushButton* btn = new QPushButton (text, this);

    connect (btn, SIGNAL (clicked ()), SLOT (buttonClicked ()));
    _layout->addWidget (btn);
    _buttons.append (btn);

    return *this;
}


void MenuDialog::buttonClicked ()
{
    QPushButton *btn = static_cast<QPushButton*> (sender ());

    if (!btn)
        return;

    index = _buttons.indexOf (btn);

    accept ();
}


int MenuDialog::run ()
{
    index = -1;

    if (exec () == QDialog::Accepted)
        return index;
    else
        return -1;
}


