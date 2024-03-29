// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: SampleImportPlugin.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Import plugin for sample source files.
//-----------------------------------------------------------------------------

#ifndef SAMPLEIMPORTER_H
#define SAMPLEIMPORTER_H

#include "sampleimport_global.h"

#include <KactusAPI/include/ImportPlugin.h>
#include <KactusAPI/include/HighlightSource.h>

#include <QSharedPointer>
#include <QString>

#include <SampleImportSettingsModel.h>

class Component;
class View;

//-----------------------------------------------------------------------------
//! Import plugin for sample source files.
//-----------------------------------------------------------------------------
class SAMPLEIMPORT_EXPORT SampleImportPlugin: public QObject, public ImportPlugin, public HighlightSource
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "kactus2.plugins.sampleImport" FILE "sampleImport.json")
    Q_INTERFACES(IPlugin)
    Q_INTERFACES(ImportPlugin)

public:

    //! The constructor.
    SampleImportPlugin();

    //! The destructor.
    ~SampleImportPlugin();
    
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
    virtual QString getLicense() const;
    
    /*!
     *  Returns the licence holder of the plugin.
     */
    virtual QString getLicenseHolder() const;
    
    /*!
     *  Returns the settings widget.
     */
    virtual QWidget* getSettingsWidget();

    /*!
     *  This is used to access the settings modified by function getSettingsModel().
     */
    virtual PluginSettingsModel* getSettingsModel();

    /*! 
     *   Returns the external program requirements of the plugin.
     */
    virtual QList<ExternalProgramRequirement> getProgramRequirements();
    
    /*!
     *  Returns the supported import file types.
     *
     *      @return The file types the import parser supports.
     */
    virtual QStringList getSupportedFileTypes() const;
    
    /*!
     *  Returns a compatibility warning concerning the import plugin usage.
     *
     *      @return The warning text.
     */
    virtual QString getCompatibilityWarnings() const;
    
    /*!
     *  Runs the import by parsing the given input and applying the parsed elements to the given component.
     *
     *      @param [in] input                   The input text to parse.
     *      @param [in] componentDeclaration    The input text to parse.
     *      @param [in] targetComponent         The component to apply all imported changes to.
     */
    void import(QString const& input, QString const& componentDeclaration, QSharedPointer<Component> targetComponent) override;
    
    /*!
     *  Sets the given highlighter to be used by the source.
     *
     *      @param [in] highlighter   The highlighter to use.          
     */
    virtual void setHighlighter(Highlighter* highlighter);

    /*!
     *  Get component declarations from the selected input file.
     *
     *      @param [in] input   The selected input file.
     *
     *      @return List of component declarations found in the selected input.
     */
    QStringList getFileComponents(QString const& input) const override;

    /*!
     *  Get the name of the selected component declaration.
     *
     *      @param [in] componentDeclaration    The selected component declaration.
     *
     *      @return Name of the selected component declaration.
     */
    QString getComponentName(QString const& componentDeclaration) const override;


private:

    // Disable copying.
    SampleImportPlugin(SampleImportPlugin const& rhs);
    SampleImportPlugin& operator=(SampleImportPlugin const& rhs);

    //! The highlighter to use.
    Highlighter* highlighter_;

    //! The settings model to use.
    SampleImportSettingsModel* settingsModel_;
};

#endif // SAMPLEIMPORTER_H
