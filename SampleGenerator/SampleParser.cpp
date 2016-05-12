//-----------------------------------------------------------------------------
// File: SampleParser.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Parses design for sample data.
//-----------------------------------------------------------------------------

#include "SampleParser.h"

#include <IPXACTmodels/Component/Component.h>

//-----------------------------------------------------------------------------
// Function: SampleParser::SampleParser()
//-----------------------------------------------------------------------------
SampleParser::SampleParser()
{
}

//-----------------------------------------------------------------------------
// Function: SampleParser::~SampleParser()
//-----------------------------------------------------------------------------
SampleParser::~SampleParser()
{
}

//-----------------------------------------------------------------------------
// Function: SampleParser::getParsedData()
//-----------------------------------------------------------------------------
QList<SampleParser::SampleData>& SampleParser::getParsedData()
{
    return parsedData_;
}

//-----------------------------------------------------------------------------
// Function: SampleParser::parse()
//-----------------------------------------------------------------------------
void SampleParser::parse(LibraryInterface* library, QSharedPointer<const Design> design)
{
	// List of matching components.
	QList<QSharedPointer<const Component>> components;

	// Go through hardware instances.
    foreach (QSharedPointer<ComponentInstance> instance, *design->getComponentInstances())
    {
        // The VLNV and the component of the instance are needed.
        QSharedPointer<VLNV> vlnv = instance->getComponentRef();
        QSharedPointer<const Component> fileComponent = library->getModelReadOnly(*vlnv).dynamicCast<const Component>();

		// Append to the list of found components.
		components.append(fileComponent);
    }

	// Go through software instances (a kactus2 extension).
	foreach (QSharedPointer<SWInstance> instance, design->getSWInstances())
	{
		// The VLNV and the component of the instance are needed.
		QSharedPointer<VLNV> vlnv = instance->getComponentRef();
		QSharedPointer<const Component> fileComponent = library->getModelReadOnly(*vlnv).dynamicCast<const Component>();

		// Append to the list of found components.
		components.append(fileComponent);
	}

	foreach ( QSharedPointer<const Component> fileComponent, components )
	{
		// Cull all filesets with matching name.
		foreach ( QSharedPointer<FileSet> fileSet, *fileComponent->getFileSets() )
		{
			if ( fileSet->name() == "src" )
			{
				// Create entry and append.
				SampleData s;
				s.fileSet = fileSet;
				parsedData_.append(s);
			}
		}
	}
}