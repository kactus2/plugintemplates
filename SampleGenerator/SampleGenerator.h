// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: SampleGenerator.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Sample generator.
//-----------------------------------------------------------------------------

#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#include "SampleParser.h"

#include <Plugins/PluginSystem/IPluginUtility.h>

class SampleGenerator
{
public:
    SampleGenerator( SampleParser& parser, IPluginUtility* utility );

    ~SampleGenerator();

    /*!
     *  Prints how much we have parsed data.
     */
    void generate() const;

private:
    //! Collection of data sets, one for each Sample.
    QList<SampleParser::SampleData> parsedData_;
    //! The utility used to print message and etc.
    IPluginUtility* utility_;
};

#endif // SAMPLEGENERATOR_H
