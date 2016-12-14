//-----------------------------------------------------------------------------
// File: SampleGeneratorPlugin.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Sample generator plugin.
//-----------------------------------------------------------------------------

#ifndef SAMPLEGENERATORPLUGIN_H
#define SAMPLEGENERATORPLUGIN_H

#include "samplegenerator_global.h"

#include <Plugins/PluginSystem/GeneratorPlugin/IGeneratorPlugin.h>
#include <Plugins/PluginSystem/IPluginUtility.h>

class SAMPLEGENERATOR_EXPORT SampleGeneratorPlugin : public QObject, public IGeneratorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "kactus2.plugins.sampleGenerator" FILE "sampleGenerator.json")

    Q_INTERFACES(IPlugin)
    Q_INTERFACES(IGeneratorPlugin)

public:
    //! The constructor.
    SampleGeneratorPlugin();
    
    //! The destructor.
    ~SampleGeneratorPlugin();

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
     *  Returns the icon for the generator.
     */
    virtual QIcon getIcon() const;
    
    /*!
     *  Checks whether the generator may run for the given component or design. 
     *
     *      @param [in] libComp         The component for which to check support. If libDes is not null, libComp
     *                                  must refer to libDes or libDesConf.
     *      @param [in] libDesConf      The design configuration for design libDes, if it is not null.
     *      @param [in] libDes          The design, if the generator is ran for a design.
     *
     *      @return True, if the generator may run the given component. Otherwise false.
     */
     virtual bool checkGeneratorSupport(QSharedPointer<Document const> libComp, 
         QSharedPointer<Document const> libDesConf = QSharedPointer<Document const>(), 
         QSharedPointer<Document const> libDes = QSharedPointer<Document const>()) const;
     
    /*!
     *  Runs the generation.
     *
     *      @param [in]         utility             The plugin utility interface.
     *      @param [in,out]     libComp             The component for which the generator is run. If libDes is not null,
     *                                              libComp must refer to libDes or libDesConf.
     *      @param [in, out]    libDesConf          The design configuration for design libDes, if it is not null.
     *      @param [in, out]    libDes              The design, if the generator is ran for a design.
     */
     virtual void runGenerator(IPluginUtility* utility,
         QSharedPointer<Document> libComp, 
         QSharedPointer<Document> libDesConf = QSharedPointer<Document const>(),
         QSharedPointer<Document> libDes = QSharedPointer<Document>());

     //! \brief Returns the external program requirements of the plugin.
     virtual QList<IPlugin::ExternalProgramRequirement> getProgramRequirements();

public slots:

    /*!
     *  Called when an error is reported to us.
     *
	 *      @param [in] report			The error message.
	 */
    void onErrorReport(const QString& report);

private:
    //! The plugin utility provided by call runGenerator.
    IPluginUtility* utility_;
};

#endif // SAMPLEGENERATORPLUGIN_H
