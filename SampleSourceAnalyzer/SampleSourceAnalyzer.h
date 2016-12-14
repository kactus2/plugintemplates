// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: SampleSourceAnalyzer.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 12.05.2016
//
// Description:
// Sample source analyzer plugin.
//-----------------------------------------------------------------------------

#ifndef SAMPLESOURCEANALYZER_H
#define SAMPLESOURCEANALYZER_H

#include "samplesourceanalyzer_global.h"

#include <Plugins/PluginSystem/ISourceAnalyzerPlugin.h>

#include <QFile>
#include <QString>

class SampleSourceAnalyzer : public QObject, public ISourceAnalyzerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "kactus2.plugins.sampleSourceAnalyzer" FILE "samplesourceanalyzer.json")

    Q_INTERFACES(IPlugin)
    Q_INTERFACES(ISourceAnalyzerPlugin)

public:
    //! The constructor
    SampleSourceAnalyzer();
    
    //! The destructor.
    ~SampleSourceAnalyzer();

    /*!
     *  Returns the name of the plugin.
     */
    virtual QString getName() const;

    /*!
     *  Returns the version of the plugin.
     */
    virtual QString getVersion() const;

    /*!
     *  Returns the description of the plugin.
     */
    virtual QString getDescription() const;

    /*!
     *  Returns the vendor of the plugin.
     */
    virtual QString getVendor() const;

    /*!
     *  Returns the licence of the plugin.
     */
    virtual QString getLicence() const;

    /*!
     *  Returns the holder of the licence of the plugin.
     */
    virtual QString getLicenceHolder() const;

    /*!
     *  Returns the settings widget.
     */
    virtual QWidget* getSettingsWidget();

    /*!
     *  This is used to access the settings modified by function getSettingsWidget().
     */
    virtual PluginSettingsModel* getSettingsModel();

    /*!
     *  Returns the list of file types this plugin can run analysis for.
     */
    virtual QStringList getSupportedFileTypes() const;

    /*!
     *  Calculates a language-dependent hash for the given file.
     *
     *      @param [in] filename  The name of the file.
     *
     *      @return The hash value for the file.
     */
    virtual QString calculateHash(QString const& filename);

    /*!
     *  This function is called once when the dependency analysis scan is started.
     *
     *      @param [in] component       The component to which the dependency scan is being run.
     *      @param [in] componentPath  The path to the directory where the component is located.
     *
     *      @remarks Any preparations needed for the file dependency analysis should be made here.
     */
    virtual void beginAnalysis(Component const* component, QString const& componentPath);

    /*!
     *  This function is called once after the dependency analysis scan has completed.
     *
     *      @param [in] component       The component to which the dependency scan is being run.
     *      @param [in] componentPath  The path to the directory where the component is located.
     *
     *      @remarks Any cleanups needed should be made here.
     */
    virtual void endAnalysis(Component const* component, QString const& componentPath);

    /*!
     *  Retrieves all file dependencies the given file has.
     *
     *      @param [in]  component      The component to which the dependency scan is being run.
     *      @param [in]  componentPath  The path to the directory where the component is located.
     *      @param [in]  filename       The name of the file to which the analysis is run.
     *      @param [out] dependencies   The list of found dependencies.
     */
    virtual QList<FileDependencyDesc> getFileDependencies(Component const* component,
                                     QString const& componentPath,
                                     QString const& filename);

     //! \brief Returns the external program requirements of the plugin.
     virtual QList<IPlugin::ExternalProgramRequirement> getProgramRequirements();

private:
    // Disable copying.
    SampleSourceAnalyzer(SampleSourceAnalyzer const& rhs);
    SampleSourceAnalyzer& operator=(SampleSourceAnalyzer const& rhs);

    //! The supported file types.
    QStringList fileTypes_;
};

#endif // SAMPLESOURCEANALYZER_H
