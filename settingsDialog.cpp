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

    _displayButton = new QMaemo5ValueButton (tr ("Display"), this);
    layout->addWidget (_displayButton);
    _updateButton = new QMaemo5ValueButton (tr ("Update"), this);
    layout->addWidget (_updateButton);
    _alertsButton = new QMaemo5ValueButton (tr ("Alerts"), this);
    layout->addWidget (_alertsButton);

    connect (_displayButton, SIGNAL (clicked ()), SLOT (displayClicked ()));
    connect (_updateButton, SIGNAL (clicked ()), SLOT (updateClicked ()));
}


void SettingsDialog::displayClicked ()
{
    DisplaySettingsDialog dlg (_settings);
    dlg.exec ();
}


void SettingsDialog::updateClicked ()
{
    UpdateSettingsDialog dlg (_settings);
    dlg.exec ();
}


// --------------------------------------------------
// BaseSettingsDialog
// --------------------------------------------------
BaseSettingsDialog::BaseSettingsDialog (Settings *settings)
    : QDialog (),
      _settings (settings),
      _layout (new QVBoxLayout)
{
    QHBoxLayout *layout = new QHBoxLayout (this);
    QVBoxLayout *right_layout = new QVBoxLayout ();

    // Right side
    _saveButton = new QPushButton (tr ("Save"), this);
    connect (_saveButton, SIGNAL (clicked ()), SLOT (saveClicked ()));

    right_layout->addStretch ();
    right_layout->addWidget (_saveButton);

    // Path them together
    layout->addLayout (_layout);
    layout->addLayout (right_layout);

    // Left side would be initialized later
}


void BaseSettingsDialog::saveClicked ()
{
    saveSettings ();
    _settings->save ();
    accept ();
}


// --------------------------------------------------
// DisplaySettingsDialog
// --------------------------------------------------
DisplaySettingsDialog::DisplaySettingsDialog (Settings *settings)
    : BaseSettingsDialog (settings)
{
    setWindowTitle (tr ("Display settings"));
    setMinimumSize (300, 400);

    initCities (layout ());
    initChecks (layout ());
}


void DisplaySettingsDialog::initCities (QBoxLayout *layout)
{
    _cities = new QListWidget (this);
    QMap<QString, QString> cities_map = settings ()->cities ();
    QMap<QString, QString>::iterator it = cities_map.begin ();

    // Populate list with cities
    while (it != cities_map.end ()) {
        QListWidgetItem *item = new QListWidgetItem (it.value (), _cities);

        item->setData (Qt::UserRole, QVariant (it.key ()));
        if (it.key () == settings ()->regionID ())
            _cities->setCurrentItem (item);
        it++;
    }

    layout->addWidget (_cities);
}


void DisplaySettingsDialog::initChecks (QBoxLayout *layout)
{
    QGridLayout *grid = new QGridLayout;

    _showLight = new QCheckBox (tr ("Light"), this);
    _showLight->setChecked (settings ()->check (Settings::C_Light));
    _showRank = new QCheckBox (tr ("Rank"), this);
    _showRank->setChecked (settings ()->check (Settings::C_Rank));
    _showTime = new QCheckBox (tr ("Time"), this);
    _showTime->setChecked (settings ()->check (Settings::C_Time));
    _showHint = new QCheckBox (tr ("Hint"), this);
    _showHint->setChecked (settings ()->check (Settings::C_Hint));

    grid->addWidget (_showLight, 0, 0);
    grid->addWidget (_showRank, 0, 1);
    grid->addWidget (_showTime, 1, 0);
    grid->addWidget (_showHint, 1, 1);

    layout->addLayout (grid);
}


void DisplaySettingsDialog::saveSettings ()
{
    QListWidgetItem *cur = _cities->currentItem ();

    if (cur)
        settings ()->setRegionID (cur->data (Qt::UserRole).toString ());

    settings ()->setCheck (Settings::C_Light, _showLight->isChecked ());
    settings ()->setCheck (Settings::C_Rank,  _showRank->isChecked ());
    settings ()->setCheck (Settings::C_Time,  _showTime->isChecked ());
    settings ()->setCheck (Settings::C_Hint,  _showHint->isChecked ());
}


// --------------------------------------------------
// UpdateSettingsDialog
// --------------------------------------------------
UpdateSettingsDialog::UpdateSettingsDialog (Settings *settings)
    : BaseSettingsDialog (settings)
{
    setWindowTitle (tr ("Update settings"));
}


void UpdateSettingsDialog::saveSettings ()
{
}
