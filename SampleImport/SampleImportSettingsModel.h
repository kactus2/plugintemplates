//-----------------------------------------------------------------------------
// File: SampleImportSettingsModel.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 16.11.2016
//
// Description:
// A plugin settings model.
//-----------------------------------------------------------------------------

#ifndef SAMPLEIMPORTSETTINGSMODEL_H
#define SAMPLEIMPORTSETTINGSMODEL_H

#include <Plugins/PluginSystem/PluginSettingsModel.h>

//-----------------------------------------------------------------------------
//! A plugin settings model.
//-----------------------------------------------------------------------------
class SampleImportSettingsModel : public QObject, public PluginSettingsModel
{
    Q_OBJECT

public:
    struct runtimeData
    {
        //! If true, main should be included for highlights. Else false.
        bool findMain;
        //! The suffix that is to be appended to the names of imported ports.
        QString portSuffix;
    };

    /*!
     *  Constructor.
     */
    SampleImportSettingsModel();

    /*!
     *  Destructor.
     */
    virtual ~SampleImportSettingsModel();
    
    /*!
     *  Loads plugin settings from the given settings store.
     *
     *      @param [in] settings The settings store.
     */
    virtual void loadSettings(QSettings& settings);
    
    /*!
     *  Saves plugin settings to the given settings store.
     *
     *      @param [in,out] settings The settings store.
     */
    virtual void saveSettings(QSettings& settings);

    /*!
     *  Validates the settings of the plugin.
     */
    virtual bool validateSettings() const;
    
    /*!
     *  Returns pointer to the current settings.
     */
    runtimeData* getCurrentSettings();
    
    /*!
     *  Returns pointer to the settings that will take effect when applying.
     */
    runtimeData* getPendingSettings();

signals:
	
    /*!
     *  Emitted when error occurred in the model.
     */
	void errorOccurred(const QString &) const;

private:

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The current settings.
    runtimeData currentSettings_;
    //! The not-yet-accepted settings.
    runtimeData pendingSettings_;
};

//-----------------------------------------------------------------------------

#endif // SAMPLEIMPORTSETTINGSMODEL_H
