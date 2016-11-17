//-----------------------------------------------------------------------------
// File: SampleImportSettingsModel.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 16.11.2016
//
// Description:
// A plugin settings model.
//-----------------------------------------------------------------------------

#include "SampleImportSettingsModel.h"

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::SampleImportSettingsModel()
//-----------------------------------------------------------------------------
SampleImportSettingsModel::SampleImportSettingsModel()
{
    currentSettings_.findMain = true;
    currentSettings_.portSuffix = QLatin1String("");

    pendingSettings_ = currentSettings_;
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::~SampleImportSettingsModel()
//-----------------------------------------------------------------------------
SampleImportSettingsModel::~SampleImportSettingsModel()
{
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::loadSettings()
//-----------------------------------------------------------------------------
void SampleImportSettingsModel::loadSettings(QSettings& settings)
{
    currentSettings_.findMain = settings.value("/findMain", true).toBool();
    currentSettings_.portSuffix = settings.value("/portSuffix").toString();
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::saveSettings()
//-----------------------------------------------------------------------------
void SampleImportSettingsModel::saveSettings(QSettings& settings)
{
    currentSettings_ = pendingSettings_;

    settings.setValue("/findMain", currentSettings_.findMain);
    settings.setValue("/portSuffix", currentSettings_.portSuffix);
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::validateSettings()
//-----------------------------------------------------------------------------
bool SampleImportSettingsModel::validateSettings() const
{
    bool suffixOk = pendingSettings_.portSuffix.size() < 10;

    if (!suffixOk)
    {
        emit errorOccurred("Too long suffix!");
    }

    return suffixOk;
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::getCurrentSettings()
//-----------------------------------------------------------------------------
SampleImportSettingsModel::runtimeData* SampleImportSettingsModel::getCurrentSettings()
{
    return &currentSettings_;
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsModel::getPendingSettings()
//-----------------------------------------------------------------------------
SampleImportSettingsModel::runtimeData* SampleImportSettingsModel::getPendingSettings()
{
    return &pendingSettings_;
}