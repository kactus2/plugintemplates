//-----------------------------------------------------------------------------
// File: SampleImportSettingsWidget.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 16.11.2016
//
// Description:
// A plugin settings widget.
//-----------------------------------------------------------------------------

#include "SampleImportSettingsWidget.h"
#include "SampleImportSettingsModel.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QFormLayout>

//-----------------------------------------------------------------------------
// Function:  SampleImportSettingsWidget:: SampleImportSettingsWidget()
//-----------------------------------------------------------------------------
SampleImportSettingsWidget::SampleImportSettingsWidget
    (SampleImportSettingsModel* model) : model_(model), labelError_(new QLabel)
{
    // Layout to contain widgets.
    QFormLayout* viewSelectionLayout = new QFormLayout(this);

    // Check box for finding main, initialize with the current value.
    QCheckBox* mainBox = new QCheckBox();
    mainBox->setChecked(model->getCurrentSettings()->findMain);
    viewSelectionLayout->addRow(tr("Find main:"), mainBox);

    // The suffix for port names, initialize with the current value.
    QLineEdit* suffix = new QLineEdit();
    suffix->setText(model->getCurrentSettings()->portSuffix);
    viewSelectionLayout->addRow(tr("Suffix for ports:"), suffix);

    // The error label comes last.
    viewSelectionLayout->addWidget(labelError_);

    // Connect the relevant signals from the children to the slots in the parent.
    connect(mainBox, SIGNAL(stateChanged(int)), 
        this, SLOT(onStateChanged(int)), Qt::UniqueConnection);
    connect(suffix, SIGNAL(textChanged(const QString &)), this,
        SLOT(onSuffixEdited(const QString &)), Qt::UniqueConnection);

    // Connect the signal from the model to a slot in the widget.
    connect(model_, SIGNAL(errorOccurred(const QString &)), 
        this, SLOT(onError(const QString &)), Qt::UniqueConnection);
}

//-----------------------------------------------------------------------------
// Function: FileOutputWidget::~SampleImportSettingsWidget()
//-----------------------------------------------------------------------------
SampleImportSettingsWidget::~SampleImportSettingsWidget()
{
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsWidget::onStateChanged()
//-----------------------------------------------------------------------------
void SampleImportSettingsWidget::onStateChanged(int state)
{
    model_->getPendingSettings()->findMain = state == Qt::Checked;
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsWidget::onSuffixEdited()
//-----------------------------------------------------------------------------
void SampleImportSettingsWidget::onSuffixEdited(const QString &text)
{
    model_->getPendingSettings()->portSuffix = text;
}

//-----------------------------------------------------------------------------
// Function: SampleImportSettingsWidget::onError()
//-----------------------------------------------------------------------------
void SampleImportSettingsWidget::onError(const QString &text)
{
    labelError_->setText(text);
}
