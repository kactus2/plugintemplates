//-----------------------------------------------------------------------------
// File: SampleImportPlugin.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Sample import plugin for sample source files.
//-----------------------------------------------------------------------------

#include "SampleImportPlugin.h"

#include <IPXACTmodels/Component/Component.h>
#include <Plugins/PluginSystem/ImportPlugin/ImportColors.h>

#include <QString>
#include <QRegularExpression>

//-----------------------------------------------------------------------------
// Function: SampleImport::SampleImport()
//-----------------------------------------------------------------------------
SampleImportPlugin::SampleImportPlugin(): QObject(0), highlighter_(0)
{

}

//-----------------------------------------------------------------------------
// Function: SampleImport::~SampleImport()
//-----------------------------------------------------------------------------
SampleImportPlugin::~SampleImportPlugin()
{

}

//-----------------------------------------------------------------------------
// Function: SampleImport::getName()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getName() const
{
    return "Sample importer";
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getVersion()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getVersion() const
{
    return "1.0";
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getDescription()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getDescription() const
{
    return "Highlight the first main and return value of a C/C++ file.";
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getVendor()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getVendor() const
{
    return tr("TUT");
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getLicence()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getLicence() const
{
    return tr("MIT");
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getLicenceHolder()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getLicenceHolder() const
{
    return tr("Public");
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getSettingsWidget()
//-----------------------------------------------------------------------------
PluginSettingsWidget* SampleImportPlugin::getSettingsWidget()
{
    return new PluginSettingsWidget();
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getProgramRequirements()
//-----------------------------------------------------------------------------
QList<IPlugin::ExternalProgramRequirement> SampleImportPlugin::getProgramRequirements()
{
    return QList<IPlugin::ExternalProgramRequirement>();
}

//-----------------------------------------------------------------------------
// Function: SampleImport::acceptedFileTypes()
//-----------------------------------------------------------------------------
QStringList SampleImportPlugin::getSupportedFileTypes() const
{
    QStringList supportedTypes;
    supportedTypes << "cSource" << "cppSource";

    return supportedTypes;
}

//-----------------------------------------------------------------------------
// Function: SampleImport::getCompatibilityWarnings()
//-----------------------------------------------------------------------------
QString SampleImportPlugin::getCompatibilityWarnings() const
{
    return QString();
}

//-----------------------------------------------------------------------------
// Function: SampleImport::import()
//-----------------------------------------------------------------------------
void SampleImportPlugin::import(QString const& input, QSharedPointer<Component> targetComponent)
{
	// Highlight word main.
	highlighter_->applyHighlight(QString("main"), ImportColors::VIEWNAME);

	// Rule for finding a return statement: keyword + white space + alphanumeric symbol.
	const QRegularExpression RETURN_RULE( "return\\s\\w+;" );

	// Find it.
	QRegularExpressionMatch returnS = RETURN_RULE.match(input);

	// Needs start and end locations for highlight.
	int returnStart = returnS.capturedStart();
	int returnEnd = returnS.capturedEnd();

	// Apply the highlight.
	highlighter_->applyHighlight(returnStart, returnEnd, ImportColors::MODELPARAMETER);

	// Get the sample port.
	QString portName = "Sample";
	QSharedPointer<Port> port = targetComponent->getPort(portName);

	// If it does not exist, create and append to the ports.
	if ( !port )
	{
		port = QSharedPointer<Port>(new Port());       
		targetComponent->getPorts()->append(port);
		port->setName(portName);
	}
}

//-----------------------------------------------------------------------------
// Function: SampleImport::setHighlighter()
//-----------------------------------------------------------------------------
void SampleImportPlugin::setHighlighter(Highlighter* highlighter)
{
    highlighter_ = highlighter;
}