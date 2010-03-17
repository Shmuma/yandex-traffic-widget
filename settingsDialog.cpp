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
    _displayButton->setValueLayout (QMaemo5ValueButton::ValueUnderText);
    updateDisplayButtonValue ();
    layout->addWidget (_displayButton);
    _updateButton = new QMaemo5ValueButton (tr ("Update"), this);
    _updateButton->setValueLayout (QMaemo5ValueButton::ValueUnderText);
    updateUpdateButtonValue ();
    layout->addWidget (_updateButton);

    createLanguageButton (layout);

    connect (_displayButton, SIGNAL (clicked ()), SLOT (displayClicked ()));
    connect (_updateButton, SIGNAL (clicked ()), SLOT (updateClicked ()));
}


void SettingsDialog::createLanguageButton (QBoxLayout *layout)
{
    _languageButton = new QMaemo5ValueButton (tr ("Interface language"), this);
    layout->addWidget (_languageButton);

#ifdef Q_WS_MAEMO_5
    QMaemo5ListPickSelector *selector = new QMaemo5ListPickSelector;
    QStandardItemModel *model = new QStandardItemModel (0, 1);
    QList<Language>::const_iterator it = _settings->languages ().begin ();

    while (it != _settings->languages ().end ()) {
        QStandardItem *item = new QStandardItem (it->title ());
        item->setData (it->alias ());
        model->appendRow (item);
        it++;
    }

    selector->setModel (model);
    selector->setCurrentIndex (_settings->languages ().indexOf (_settings->language ()));

    _languageButton->setPickSelector (selector);

    connect (selector, SIGNAL (selected (const QString&)), SLOT (languageChanged (const QString&)));
#endif
}


void SettingsDialog::displayClicked ()
{
    DisplaySettingsDialog dlg (_settings);
    dlg.exec ();
    updateDisplayButtonValue ();
}


void SettingsDialog::updateClicked ()
{
    UpdateSettingsDialog dlg (_settings);
    dlg.exec ();
    updateUpdateButtonValue ();
}


void SettingsDialog::languageChanged (const QString&)
{
#ifdef Q_WS_MAEMO_5
    QMaemo5ListPickSelector *model = static_cast<QMaemo5ListPickSelector*> (_languageButton->pickSelector ());

    if (!model)
        return;

    _settings->setLanguageIndex (model->currentIndex ());
    _settings->save ();
#endif
}


void SettingsDialog::updateDisplayButtonValue ()
{
    QString val;
    QStringList list;

    val = tr ("City:") + " " + _settings->regionName (_settings->regionID ()) + ", " + tr ("Display:") + " ";

    if (_settings->check (Settings::C_ShowLight))
        list.append (tr ("lights"));
    if (_settings->check (Settings::C_ShowRank))
        list.append (tr ("rank"));
    if (_settings->check (Settings::C_ShowTime))
        list.append (tr ("time"));
    if (_settings->check (Settings::C_ShowHint))
        list.append (tr ("hint"));

    _displayButton->setValueText (val + list.join (", "));
}


void SettingsDialog::updateUpdateButtonValue ()
{
    QStringList list, intervals = _settings->updateIntervals ();
    QString val;

    val = tr ("Interval:") + " " + intervals[_settings->getUpdateIntervalIndex ()] + ", " + tr ("Update via:") + " ";

    if (_settings->check (Settings::C_UpdateOnWiFi))
        list.append (tr ("WiFi"));
    if (_settings->check (Settings::C_UpdateOnGSM))
        list.append (tr ("GSM"));

    val += list.join (", ");

    if (_settings->check (Settings::C_UpdateWhenLocked))
        val += ", " + tr ("Update when locked");
    else
        val += ", " + tr ("Not update when locked");

    _updateButton->setValueText (val);
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
    QSizePolicy policy;

    // Right side
    _saveButton = new QPushButton (tr ("Save"), this);
    policy = _saveButton->sizePolicy ();
    policy.setHorizontalPolicy (QSizePolicy::Maximum);
    _saveButton->setSizePolicy (policy);
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
DisplaySettingsDialog::DisplaySettingsDialog (Settings *_settings)
    : BaseSettingsDialog (_settings)
{
    setWindowTitle (tr ("Display settings"));
    setMinimumSize (300, 400);

    initCities (layout ());
    initChecks (layout ());
}


void DisplaySettingsDialog::initCities (QBoxLayout *layout)
{
    _cities = new QListWidget (this);
    QStringList regions = settings ()->regionIDs ();
    QStringList::const_iterator it = regions.begin ();

    // Populate list with cities
    while (it != regions.end ()) {
        QListWidgetItem *item = new QListWidgetItem (settings()->regionName (*it), _cities);

        item->setData (Qt::UserRole, QVariant (*it));
        if (*it == settings ()->regionID ())
            _cities->setCurrentItem (item);
        it++;
    }

    layout->addWidget (_cities);
}


void DisplaySettingsDialog::initChecks (QBoxLayout *layout)
{
    QGridLayout *grid = new QGridLayout;

    _showLight = new QCheckBox (tr ("Light"), this);
    _showLight->setChecked (settings ()->check (Settings::C_ShowLight));
    _showRank = new QCheckBox (tr ("Rank"), this);
    _showRank->setChecked (settings ()->check (Settings::C_ShowRank));
    _showTime = new QCheckBox (tr ("Time"), this);
    _showTime->setChecked (settings ()->check (Settings::C_ShowTime));
    _showHint = new QCheckBox (tr ("Hint"), this);
    _showHint->setChecked (settings ()->check (Settings::C_ShowHint));

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

    settings ()->setCheck (Settings::C_ShowLight, _showLight->isChecked ());
    settings ()->setCheck (Settings::C_ShowRank,  _showRank->isChecked ());
    settings ()->setCheck (Settings::C_ShowTime,  _showTime->isChecked ());
    settings ()->setCheck (Settings::C_ShowHint,  _showHint->isChecked ());
}


// --------------------------------------------------
// UpdateSettingsDialog
// --------------------------------------------------
UpdateSettingsDialog::UpdateSettingsDialog (Settings *_settings)
    : BaseSettingsDialog (_settings)
{
    setWindowTitle (tr ("Update settings"));

    _wifiUpdate = new QCheckBox (tr ("Update via WiFi"), this);
    _wifiUpdate->setChecked (settings ()->check (Settings::C_UpdateOnWiFi));
    _gsmUpdate  = new QCheckBox (tr ("Update via GSM"), this);
    _gsmUpdate->setChecked (settings ()->check (Settings::C_UpdateOnGSM));
    _lockedUpdate  = new QCheckBox (tr ("Update when device locked"), this);
    _lockedUpdate->setChecked (settings ()->check (Settings::C_UpdateWhenLocked));

    initUpdateInterval (layout ());

    layout ()->addWidget (_wifiUpdate);
    layout ()->addWidget (_gsmUpdate);
    layout ()->addWidget (_lockedUpdate);
}


void UpdateSettingsDialog::saveSettings ()
{
#ifdef Q_WS_MAEMO_5
    QMaemo5ListPickSelector *selector = static_cast<QMaemo5ListPickSelector*> (_intervalButton->pickSelector ());

    if (selector)
        settings ()->setUpdateIntervalIndex (selector->currentIndex ());
#endif
    settings ()->setCheck (Settings::C_UpdateOnWiFi, _wifiUpdate->isChecked ());
    settings ()->setCheck (Settings::C_UpdateOnGSM,  _gsmUpdate->isChecked ());
    settings ()->setCheck (Settings::C_UpdateWhenLocked,  _lockedUpdate->isChecked ());
}


void UpdateSettingsDialog::initUpdateInterval (QBoxLayout *layout)
{
    _intervalButton = new QMaemo5ValueButton (tr ("Update interval"), this);
    layout->addWidget (_intervalButton);

#ifdef Q_WS_MAEMO_5
    QMaemo5ListPickSelector *selector = new QMaemo5ListPickSelector;
    QStandardItemModel *model = new QStandardItemModel (0, 1);
    QStringList updateIntervals = settings ()->updateIntervals ();
    QStringList::iterator it = updateIntervals.begin ();

    while (it != updateIntervals.end ()) {
        model->appendRow (new QStandardItem (*it));
        it++;
    }

    selector->setModel (model);
    selector->setCurrentIndex (settings ()->getUpdateIntervalIndex ());

    _intervalButton->setPickSelector (selector);
#endif
}
