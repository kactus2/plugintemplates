//-----------------------------------------------------------------------------
// File: SampleGenerator.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Sample generator.
//-----------------------------------------------------------------------------

#include "SampleGenerator.h"

#include <IPXACTmodels/Component/FileSet.h>
#include <QTextStream>
#include <QFileInfo>

//-----------------------------------------------------------------------------
// Function: SampleGenerator::SampleGenerator()
//-----------------------------------------------------------------------------
SampleGenerator::SampleGenerator( QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData,
	IPluginUtility* utility ) : parsedData_( parsedData ), utility_( utility )
{
}

//-----------------------------------------------------------------------------
// Function: SampleGenerator::~SampleGenerator()
//-----------------------------------------------------------------------------
SampleGenerator::~SampleGenerator()
{
}

//-----------------------------------------------------------------------------
// Function: SampleGenerator::generate()
//-----------------------------------------------------------------------------
void SampleGenerator::generate(QSharedPointer<Component> topComponent)
{
	// Print info about results.
	utility_->printInfo( QObject::tr("Found %1 matching file sets.").arg(parsedData_->count()) );

	// Find a fitting file set from the top component,
	QString fileSetName = QString("sampleFileSet");
	QSharedPointer<FileSet> fileSet = topComponent->getFileSet(fileSetName);

	// Create and add to the top component if needed.
	if (!fileSet)
	{
		fileSet = QSharedPointer<FileSet>(new FileSet(fileSetName, "sourceFiles"));
		topComponent->getFileSets()->append(fileSet);
	}

	// Get the path to the top component.
	QString componentXmlPath = utility_->getLibraryInterface()->getPath(topComponent->getVlnv());
	QFileInfo pathInfo(componentXmlPath);

	// The new file will be in the same path.
	QString filePath = pathInfo.absolutePath() + "/sampleGeneratedFile.txt";
	QFile sampleFile(filePath);

	// If it cannot be written, then it is too bad.
	if ( !sampleFile.open(QIODevice::WriteOnly) )
	{
		utility_->printError("Could not open the sample at location " + filePath);
		utility_->printError("Reason: " + sampleFile.errorString());
		return;
	}

	// Nicer to handle as a stream.
	QTextStream outStream(&sampleFile);

	// The content: Name of each found file set.
	foreach( QSharedPointer<SampleParser::SampleData> data, *parsedData_ )
	{
		outStream << data->fileSet->name() << endl;
	}

	// Close after it is done.
	sampleFile.close();

	// Add the file to file set. Notice that the path is relative to the xml file of the
	// component where the file belongs to.
	auto sampleIPXACTFile = QSharedPointer<File>( new File( "sampleGeneratedFile.txt", "textFile" ) );
	fileSet->addFile(sampleIPXACTFile);
}