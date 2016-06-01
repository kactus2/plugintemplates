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
#include <IPXACTmodels/Component/Component.h>

class SampleGenerator
{
public:
    /*!
     *  The constructor
     *
     *      @param [in] parsedData	The data parsed by sample parser.
     *      @param [in] utility		The utility interface provided for the plugin.
     */
    SampleGenerator( QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData,
		IPluginUtility* utility );

    ~SampleGenerator();

    /*!
	*  Generates a file with the names of the file sets within the parsed data.
	*
	*      @param [in] topComponent	The top component of the design, where the generation is based to.
	*/
    void generate( QSharedPointer<Component> topComponent );

private:
    //! Collection of data sets, one for each Sample.
    QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData_;
    //! The utility used to print message and etc.
    IPluginUtility* utility_;
};

#endif // SAMPLEGENERATOR_H
