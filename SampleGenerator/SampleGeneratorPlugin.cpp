// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: SampleGeneratorPlugin.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Sample generator plugin.
//-----------------------------------------------------------------------------

#include "SampleGenerator.h"
#include "SampleGeneratorPlugin.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QMessageBox>

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::SampleGeneratorPlugin()
//-----------------------------------------------------------------------------
SampleGeneratorPlugin::SampleGeneratorPlugin() : QObject(0)
{

}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::SampleGeneratorPlugin()
//-----------------------------------------------------------------------------
SampleGeneratorPlugin::~SampleGeneratorPlugin()
{

}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getName()
//----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getName() const
{
    return "Sample Generator";
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getVersion()
//-----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getVersion() const
{
    return "1.0";
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getDescription()
//-----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getDescription() const
{
    return "Gathers each file set from design containing at least one file and generates a file with the names "\
           "of the file sets.";
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getVendor()
//-----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getVendor() const
{
    return tr("Insert vendor here");
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getLicence()
//-----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getLicence() const
{
    return tr("MIT");
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getLicenceHolder()
//-----------------------------------------------------------------------------
QString SampleGeneratorPlugin::getLicenceHolder() const
{
    return tr("Public");
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getSettingsWidget()
//-----------------------------------------------------------------------------
QWidget* SampleGeneratorPlugin::getSettingsWidget()
{
    return new QWidget();
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getSettingsModel()
//-----------------------------------------------------------------------------
PluginSettingsModel* SampleGeneratorPlugin::getSettingsModel()
{
    return NULL;
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getIcon()
//-----------------------------------------------------------------------------
QIcon SampleGeneratorPlugin::getIcon() const
{
    return QIcon(":icons/SampleGenerator.png");
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::checkGeneratorSupport()
//-----------------------------------------------------------------------------
bool SampleGeneratorPlugin::checkGeneratorSupport( QSharedPointer<Document const> libComp,
    QSharedPointer<Document const> libDesConf,
    QSharedPointer<Document const> libDes ) const
{
    // Must be ran on a design.
    return ( libDes != 0 && libDesConf != 0 );
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::runGenerator()
//-----------------------------------------------------------------------------
void SampleGeneratorPlugin::runGenerator(IPluginUtility* utility, 
    QSharedPointer<Document> libComp,
    QSharedPointer<Document> libDesConf,
    QSharedPointer<Document> libDes)
{
    // This is needed as a member variable to be used more conveniently.
    utility_ = utility;

    // Dynamic cast to component, as it is needed that way.
    QSharedPointer<Component> topComponent = libComp.dynamicCast<Component>();
    // Dynamic cast to design, as it is needed that way.
    QSharedPointer<const Design> design = libDes.dynamicCast<Design const>();

    // In principle, these could be null. They must not be.
    if (!topComponent || !design)
    {
        utility->printError( "Sample generator received null top component or design!" );
    }

    // Parse the matching file sets.
    SampleParser sparser;
    sparser.parse(utility->getLibraryInterface(),design);

    // Print info about results.
    utility->printInfo(QObject::tr("Found %1 matching file sets.").arg(sparser.getParsedData()->count()));

    // Initialize generator, provide the parsed data, catch its error signals.
    SampleGenerator sgenerator(sparser.getParsedData());
    connect(&sgenerator, SIGNAL(reportError(const QString&)), 
        this, SLOT(onErrorReport(const QString&)), Qt::UniqueConnection);

    // Get the path to the top component: The new file will be in the same path.
    QString componentXmlPath = utility->getLibraryInterface()->getPath(topComponent->getVlnv());
    QFileInfo pathInfo(componentXmlPath);

    // Generate.
    sgenerator.generate(topComponent, pathInfo.absolutePath());

    // Inform when done.
    utility->printInfo( "Sample generation complete." );

    // Top component may have been affected by changes -> save.
    utility->getLibraryInterface()->writeModelToFile(libComp);
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin::getProgramRequirements()
//-----------------------------------------------------------------------------
QList<IPlugin::ExternalProgramRequirement> SampleGeneratorPlugin::getProgramRequirements()
{
    return QList<IPlugin::ExternalProgramRequirement>();
}

//-----------------------------------------------------------------------------
// Function: SampleGeneratorPlugin:::onErrorReport()
//-----------------------------------------------------------------------------
void SampleGeneratorPlugin::onErrorReport(const QString& report)
{
    utility_->printError(report);
}
