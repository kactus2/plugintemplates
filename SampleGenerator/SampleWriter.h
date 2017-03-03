//-----------------------------------------------------------------------------
// File: SampleWriter.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 11.05.2016
//
// Description:
// Writer for the sample generator.
//-----------------------------------------------------------------------------

#ifndef SAMPLEWRITER_H
#define SAMPLEWRITER_H

#include "samplegenerator_global.h"
#include "SampleParser.h"

#include <IPXACTmodels/Component/Component.h>

class SampleWriter : public QObject
{
    Q_OBJECT

public:
    /*!
     *  The constructor
     *
     *      @param [in] parsedData    The data parsed by sample parser.
     */
    SampleWriter(QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData);

    //! The destructor.
    ~SampleWriter();

    /*!
    *  Writes a file with the names of the file sets within the parsed data.
    *
    *      @param [in] topComponent         The top component of the design, where the written file will be placed.
    *      @param [in] componentXmlPath     The absolute path to the topComponent.
    */
    void write(QSharedPointer<Component> topComponent, const QString& outputPath);

signals:
	
    /*!
     *  Emitted when reportable error occurs.
     */
	void reportError(const QString& errorMessage) const;

private:

    //! The parsed data to be used in the generation.
    QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > parsedData_;
};

#endif // SAMPLEWRITER_H
