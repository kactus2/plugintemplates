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
SampleGenerator::SampleGenerator(QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData)
    : QObject(0), parsedData_(parsedData)
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
void SampleGenerator::generate(QSharedPointer<Component> topComponent, const QString& outputPath)
{
    // Find a fitting file set from the top component,
    QString fileSetName = QString("sampleFileSet");
    QSharedPointer<FileSet> fileSet = topComponent->getFileSet(fileSetName);

    // Create and add to the top component if needed.
    if (!fileSet)
    {
        fileSet = QSharedPointer<FileSet>(new FileSet(fileSetName, "sourceFiles"));
        topComponent->getFileSets()->append(fileSet);
    }

    // The path for the new file.
    QString filePath = outputPath + "/sampleGeneratedFile.txt";
    QFile sampleFile(filePath);

    // If it cannot be written, then it is too bad.
    if (!sampleFile.open(QIODevice::WriteOnly))
    {
        emit reportError(tr("Could not open the output file at location %1").arg(filePath));
        emit reportError(tr("Reason: %1").arg(sampleFile.errorString()));
        return;
    }

    // Nicer to handle as a stream.
    QTextStream outStream(&sampleFile);

    // The content: Name of each found file set.
    foreach(QSharedPointer<SampleParser::SampleData> data, *parsedData_)
    {
        outStream << data->fileSet->name() << endl;
    }

    // Close after it is done.
    sampleFile.close();

    // Add the file to file set. Notice that the path is relative to the xml file of the
    // component where the file belongs to.
    QSharedPointer<File> sampleIPXACTFile =
    QSharedPointer<File>(new File("sampleGeneratedFile.txt", "textFile"));
    fileSet->addFile(sampleIPXACTFile);
}