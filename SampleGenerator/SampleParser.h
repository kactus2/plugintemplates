// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: SampleParser.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Parses design for sample data.
//-----------------------------------------------------------------------------

#ifndef SAMPLEPARSER_H
#define SAMPLEPARSER_H

#include <QString>

#include <IPXACTmodels/Design/Design.h>
#include <IPXACTmodels/Component/FileSet.h>

#include <library/LibraryManager/libraryinterface.h>

class SampleParser
{
public:

    // A struct containing data parsed by sample parser.
    struct SampleData
    {
        // A fileset found on a component.
        QSharedPointer<FileSet> fileSet;
    };

    SampleParser();
    ~SampleParser();

    // Returns reference to all parsed SampleData.
    QSharedPointer<QList<QSharedPointer<SampleData> > > getParsedData();

    /*!
     *  Parses all components instantiated in the design and parses them for sample data.
     *
     *      @param [in] library   The library containing all components in the design.
     *      @param [in] design   The design, which component instances are being checked.
     */
    void parse( LibraryInterface* library, QSharedPointer<const Design> design );

private:

     //! Collection of data sets.
     QSharedPointer<QList<QSharedPointer<SampleData> > > parsedData_;
};

#endif // SAMPLEPARSER_H
