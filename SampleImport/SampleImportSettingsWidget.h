//-----------------------------------------------------------------------------
// File: SampleImportSettingsWidget.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 16.11.2016
//
// Description:
// A plugin settings widget.
//-----------------------------------------------------------------------------

#ifndef SAMPLEIMPORTSETTINGSWIDGET_H
#define SAMPLEIMPORTSETTINGSWIDGET_H

class SampleImportSettingsModel;

#include <QWidget>
#include <QSharedPointer>
#include <QLabel>

class SampleImportSettingsWidget : public QWidget
{
    Q_OBJECT
public:

	//! The constructor.
	SampleImportSettingsWidget(SampleImportSettingsModel* model);

	//! The destructor.
    ~SampleImportSettingsWidget();

private slots:

    /*!
     *  Will inform model about pending state change.
     */
    void onStateChanged(int state);
    
    /*!
     *  Will inform model about pending suffix change.
     */
    void onSuffixEdited(const QString &text);
    
    /*!
     *  Will display given error on the interface.
     */
    void onError(const QString &text);

private:

    // Disable copying.
    SampleImportSettingsWidget(SampleImportSettingsWidget const& rhs);
    SampleImportSettingsWidget& operator=(SampleImportSettingsWidget const& rhs);

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

	//! The model for the widget.
    SampleImportSettingsModel* model_;
    //! The label used to display errors.
    QLabel* labelError_;
};

#endif //SAMPLEIMPORTSETTINGSWIDGET_H