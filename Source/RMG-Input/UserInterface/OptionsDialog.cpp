/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "OptionsDialog.hpp"

#include <RMG-Core/Core.hpp>

using namespace UserInterface;

OptionsDialog::OptionsDialog(QWidget* parent, QString mainSettingsSection, QString settingsSection) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    this->setupUi(this);

    std::string section = settingsSection.toStdString();

    // fallback to main settings section, 
    // if the current settings section doesn't exist
    if (!CoreSettingsSectionExists(settingsSection.toStdString()))
    {
        section = mainSettingsSection.toStdString();
    }

    this->removeDuplicateMappingsCheckbox->setChecked(CoreSettingsGetBoolValue(SettingsID::Input_RemoveDuplicateMappings, section));
    this->controllerPakComboBox->setCurrentIndex(CoreSettingsGetIntValue(SettingsID::Input_Pak, section));
}

bool OptionsDialog::HasSaved()
{
    return this->hasSaved;
}

bool OptionsDialog::GetRemoveDuplicateMappings()
{
    return this->removeDuplicateMappings;
}

int OptionsDialog::GetControllerPak()
{
    return this->controllerPak;
}

void OptionsDialog::on_buttonBox_clicked(QAbstractButton *button)
{

    QPushButton *pushButton = (QPushButton *)button;
    QPushButton *okButton = this->buttonBox->button(QDialogButtonBox::Ok);

    if (pushButton == okButton)
    {
        this->hasSaved = true;
        this->removeDuplicateMappings = this->removeDuplicateMappingsCheckbox->isChecked();
        this->controllerPak = this->controllerPakComboBox->currentIndex();
    }
    
    this->accept();
}
