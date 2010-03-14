#include <QtGui>

#ifdef Q_WS_MAEMO_5
#include <QtMaemo5>
#else
#include "QtMaemo5Adapters.hpp"
#endif

#include "settingsDialog.hpp"


// --------------------------------------------------
// SettingsDialog
// --------------------------------------------------
SettingsDialog::SettingsDialog (Settings *settings)
    : QDialog (),
      _settings (settings)
{
    setWindowTitle (tr ("Settings"));

    QVBoxLayout *layout = new QVBoxLayout (this);

    displayButton = new QMaemo5ValueButton (tr ("Display"), this);
    layout->addWidget (displayButton);
    updateButton = new QMaemo5ValueButton (tr ("Update"), this);
    layout->addWidget (updateButton);
    alertsButton = new QMaemo5ValueButton (tr ("Alerts"), this);
    layout->addWidget (alertsButton);

    connect (displayButton, SIGNAL (clicked ()), SLOT (displayClicked ()));
}


void SettingsDialog::displayClicked ()
{
    DisplaySettingsDialog dlg (_settings);

    dlg.exec ();
}


// --------------------------------------------------
// DisplaySettingsDialog
// --------------------------------------------------
DisplaySettingsDialog::DisplaySettingsDialog (Settings *settings)
    : QDialog (0),
      _settings (settings)
{
    setWindowTitle (tr ("Display settings"));

    QHBoxLayout *layout = new QHBoxLayout (this);
    QVBoxLayout *left_layout = new QVBoxLayout ();
    QVBoxLayout *right_layout = new QVBoxLayout ();

    // Right side
    _saveButton = new QPushButton (tr ("&Save"), this);
    connect (_saveButton, SIGNAL (clicked ()), SLOT (saveClicked ()));

    right_layout->addStretch ();
    right_layout->addWidget (_saveButton);

    // Left side
    initCities (left_layout);
    initChecks (left_layout);

    // Pack them together
    layout->addLayout (left_layout);
    layout->addLayout (right_layout);
}


void DisplaySettingsDialog::initCities (QBoxLayout *layout)
{
    _cities = new QListWidget (this);
    QMap<QString, QString> cities_map = _settings->cities ();
    QMap<QString, QString>::iterator it = cities_map.begin ();

    // Populate list with cities
    while (it != cities_map.end ()) {
        QListWidgetItem *item = new QListWidgetItem (it.value (), _cities);

        item->setData (Qt::UserRole, QVariant (it.key ()));
        if (it.key () == _settings->regionID ())
            _cities->setCurrentItem (item);
        it++;
    }

    layout->addWidget (_cities);
}


void DisplaySettingsDialog::initChecks (QBoxLayout *layout)
{
    QGridLayout *grid = new QGridLayout;

    _showLight = new QCheckBox ("Light", this);
    _showLight->setChecked (_settings->check (Settings::C_Light));
    _showRank = new QCheckBox ("Rank", this);
    _showRank->setChecked (_settings->check (Settings::C_Rank));
    _showTime = new QCheckBox ("Time", this);
    _showTime->setChecked (_settings->check (Settings::C_Time));
    _showHint = new QCheckBox ("Hint", this);
    _showHint->setChecked (_settings->check (Settings::C_Hint));

    grid->addWidget (_showLight, 0, 0);
    grid->addWidget (_showRank, 0, 1);
    grid->addWidget (_showTime, 1, 0);
    grid->addWidget (_showHint, 1, 1);

    layout->addLayout (grid);
}


void DisplaySettingsDialog::saveClicked ()
{
    _settings->setCheck (Settings::C_Light, _showLight->isChecked ());
    _settings->setCheck (Settings::C_Rank,  _showRank->isChecked ());
    _settings->setCheck (Settings::C_Time,  _showTime->isChecked ());
    _settings->setCheck (Settings::C_Hint,  _showHint->isChecked ());
    _settings->save ();
    accept ();
}
