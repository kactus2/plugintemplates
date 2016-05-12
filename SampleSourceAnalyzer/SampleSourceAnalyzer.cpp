//-----------------------------------------------------------------------------
// File: SampleSourceAnalyzer.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Janne Virtanen
// Date: 12.05.2016
//
// Description:
// Sample source analyzer plugin.
//-----------------------------------------------------------------------------

#include "SampleSourceAnalyzer.h"

#include <QCryptographicHash>
#include <QTextStream>

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::SampleSourceAnalyzer()
//-----------------------------------------------------------------------------
SampleSourceAnalyzer::SampleSourceAnalyzer()
    : fileTypes_()
{
    fileTypes_.append("textFile");
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::~SampleSourceAnalyzer()
//-----------------------------------------------------------------------------
SampleSourceAnalyzer::~SampleSourceAnalyzer()
{
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getName()
//----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getName() const
{
    return "Sample Source Analyzer";
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getVersion()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getVersion() const
{
    return "1.0";
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getDescription()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getDescription() const
{
    return "Analyzes file dependencies from sample text files.";
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getVendor()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getVendor() const
{
    return tr("TUT");
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getLicence()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getLicence() const
{
    return tr("MIT");
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getLicenceHolder()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::getLicenceHolder() const
{
    return tr("Public");
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getSettingsWidget()
//-----------------------------------------------------------------------------
PluginSettingsWidget* SampleSourceAnalyzer::getSettingsWidget()
{
    return new PluginSettingsWidget();
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getSupportedFileTypes()
//-----------------------------------------------------------------------------
QStringList SampleSourceAnalyzer::getSupportedFileTypes() const
{
    return fileTypes_;
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::calculateHash()
//-----------------------------------------------------------------------------
QString SampleSourceAnalyzer::calculateHash(QString const& filename)
{
    // Try to open the file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // File could not be opened, return.
        return 0;
    }

    // Calculate the hash based on file name.
	// WARNING: This is not a good idea in production code.
    QCryptographicHash hash(QCryptographicHash::Sha1);
    hash.addData(file.fileName().toUtf8());

    QString result = hash.result().toHex();
    return result;
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getFileDependencies()
//-----------------------------------------------------------------------------
QList<FileDependencyDesc> SampleSourceAnalyzer::getFileDependencies(Component const* /*component*/,
                                            QString const& /*componentPath*/,
                                            QString const& filename)
{
	// List of found dependencies.
    QList<FileDependencyDesc> dependencies;

	// Open the file for readonly, no need to write it.
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
		// We decide it is easier to read in stream format.
        QTextStream sourceStream(&file);
        while(!sourceStream.atEnd())
        {
			// Next line.
            const QString currentLine = sourceStream.readLine();

			// Our "pattern": Needs + space denotes that the rest of the line contains dependency filename.
			QString need("needs ");
			int needPosition = currentLine.indexOf(need);

			// If found "needs ", proceed with this one.
			if ( needPosition != -1 )
			{
				int filePosition = needPosition + need.length();
				QString filename = currentLine.mid(filePosition);

				// If found a filename, add it as a dependency.
				if ( !filename.isEmpty() )
				{
					FileDependencyDesc dependency;
					dependency.filename = filename;
					dependencies.append(dependency);
				}
			}
        }
    }

    return dependencies;
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::beginAnalysis()
//-----------------------------------------------------------------------------
void SampleSourceAnalyzer::beginAnalysis(Component const* /*component*/, QString const& /*componentPath*/)
{
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::endAnalysis()
//-----------------------------------------------------------------------------
void SampleSourceAnalyzer::endAnalysis(Component const* /*component*/, QString const& /*componentPath*/)
{
}

//-----------------------------------------------------------------------------
// Function: SampleSourceAnalyzer::getProgramRequirements()
//-----------------------------------------------------------------------------
QList<IPlugin::ExternalProgramRequirement> SampleSourceAnalyzer::getProgramRequirements()
{
	return QList<IPlugin::ExternalProgramRequirement>();
}
