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

//-----------------------------------------------------------------------------
// Function: SampleGenerator::SampleGenerator()
//-----------------------------------------------------------------------------
SampleGenerator::SampleGenerator( SampleParser& parser, IPluginUtility* utility )
    : parsedData_( parser.getParsedData() ), utility_( utility )
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
void SampleGenerator::generate() const
{
	utility_->printInfo( QObject::tr("Found %1 matching file sets.").arg(parsedData_.count()) );
}