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

#include "samplegenerator_global.h"
#include "SampleParser.h"

#include <IPXACTmodels/Component/Component.h>

class SampleGenerator : public QObject
{
    Q_OBJECT

public:
    /*!
     *  The constructor
     *
     *      @param [in] parsedData    The data parsed by sample parser.
     */
    SampleGenerator(QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData);

    //! The destructor.
    ~SampleGenerator();

    /*!
    *  Generates a file with the names of the file sets within the parsed data.
    *
    *      @param [in] topComponent         The top component of the design, where the generated file will be placed.
    *      @param [in] componentXmlPath     The absolute path to the topComponent.
    */
    void generate(QSharedPointer<Component> topComponent, const QString& outputPath);

signals:
	
    /*!
     *  Emitted when reportable error occurs.
     */
	void reportError(const QString& errorMessage) const;

private:

    //! The parsed data to be used in the generation.
    QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData_;
};

#endif // SAMPLEGENERATOR_H
