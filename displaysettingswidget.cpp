#include "displaysettingswidget.h"

#include "experiment.h"
#include "defaultsettings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QColorDialog>

//#include <QtDebug>

DisplaySettingsWidget::DisplaySettingsWidget(Experiment *exp, QWidget *parent) :
    QDialog(parent)
{
    experiment = exp;

    this->setWindowTitle(tr("Display Settings"));

    QVBoxLayout *vertical = new QVBoxLayout;

    QGroupBox *untransformedBox = new QGroupBox(tr("Untransformed"));
    QGroupBox *transformedBox = new QGroupBox(tr("Transformed"));
    QGroupBox *palatronBox = new QGroupBox(tr("Palatron-related"));
    QGroupBox *otherBox = new QGroupBox(tr("Other"));

    QGridLayout *transformedGrid = new QGridLayout;
    QGridLayout *untransformedGrid = new QGridLayout;
    QGridLayout *palatronGrid = new QGridLayout;
    QGridLayout *otherGrid = new QGridLayout;

    untransformedBox->setLayout(untransformedGrid);
    transformedBox->setLayout(transformedGrid);
    palatronBox->setLayout(palatronGrid);
    otherBox->setLayout(otherGrid);

    vertical->addWidget(untransformedBox);
    vertical->addWidget(transformedBox);
    vertical->addWidget(palatronBox);
    vertical->addWidget(otherBox);

    QPushButton *bTraceLineColor, *bTraceDotColor;
    QPushButton *bMeasurementPointColor;
    QPushButton *ePalatronBoxColor;
    QPushButton *ePalatronDotColor;

    QPushButton *eTransformedAbstractBg;
    QPushButton *eTransformedMeasurementPoint;
    QPushButton *eTransformedTraceDot;
    QPushButton *eTransformedTraceLine;
    QPushButton *eTransformedPalatronDot;
    QPushButton *eFan;

    QSpinBox *eTraceLineWidth, *eTraceDotSize;
    QSpinBox *eMeasurementPointSize;
    QSpinBox *ePalatronBoxWidth;
    QSpinBox *ePalatronDotSize;

    bTraceLineColor = new QPushButton(tr("Trace Line Color"));
    bTraceDotColor = new QPushButton(tr("Trace Dot Color"));
    bMeasurementPointColor = new QPushButton(tr("Measurement Point Color"));
    ePalatronBoxColor = new QPushButton(tr("Palatron Box Color"));
    ePalatronDotColor = new QPushButton(tr("Palatron Dot Color"));
    eTransformedAbstractBg = new QPushButton(tr("Background"));

    eTransformedTraceLine = new QPushButton(tr("Trace Line Color"));
    eTransformedTraceDot = new QPushButton(tr("Trace Dot Color"));
    eTransformedMeasurementPoint = new QPushButton(tr("Measurement Point Color"));
    eTransformedPalatronDot = new QPushButton(tr("Palatron Dot Color"));

    eFan = new QPushButton(tr("Fan Color"));

    eTraceLineWidth = new QSpinBox;
    eTraceLineWidth->setRange(1,100);

    eTraceDotSize = new QSpinBox;
    eTraceDotSize->setRange(1,100);

    eMeasurementPointSize = new QSpinBox;
    eMeasurementPointSize->setRange(1,100);

    ePalatronBoxWidth = new QSpinBox;
    ePalatronBoxWidth->setRange(1,100);

    ePalatronDotSize = new QSpinBox;
    ePalatronDotSize->setRange(1,100);

    eTraceLineWidth->setValue(experiment->ds->nTraceWidth);
    eTraceDotSize->setValue(experiment->ds->nTraceDotSize);
    eMeasurementPointSize->setValue(experiment->ds->nMeasurementPointSize);
    ePalatronBoxWidth->setValue(experiment->ds->nPalatronBoxWidth);
    ePalatronDotSize->setValue(experiment->ds->nPalatronDotSize);


    untransformedGrid->addWidget(bTraceLineColor,1,1);
    untransformedGrid->addWidget(new QLabel(tr("Line Width")),1,2);
    untransformedGrid->addWidget(eTraceLineWidth,1,3);

    untransformedGrid->addWidget(bTraceDotColor,2,1);
    untransformedGrid->addWidget(new QLabel(tr("Dot Size")),2,2);
    untransformedGrid->addWidget(eTraceDotSize,2,3);

    untransformedGrid->addWidget(bMeasurementPointColor,3,1);
    untransformedGrid->addWidget(new QLabel(tr("Dot Size")),3,2);
    untransformedGrid->addWidget(eMeasurementPointSize,3,3);

    palatronGrid->addWidget(ePalatronBoxColor,1,1);
    palatronGrid->addWidget(new QLabel(tr("Line Width")),1,2);
    palatronGrid->addWidget(ePalatronBoxWidth,1,3);

    palatronGrid->addWidget(ePalatronDotColor,2,1);
    palatronGrid->addWidget(new QLabel(tr("Dot Size")),2,2);
    palatronGrid->addWidget(ePalatronDotSize,2,3);

    transformedGrid->addWidget(eTransformedTraceLine,1,1);
    transformedGrid->addWidget(eTransformedTraceDot,2,1);
    transformedGrid->addWidget(eTransformedMeasurementPoint,3,1);
    transformedGrid->addWidget(eTransformedPalatronDot,4,1);

    otherGrid->addWidget(eFan,1,1);

    connect(bTraceLineColor,SIGNAL(clicked()),this,SLOT(untransformedTraceLineColor()));
    connect(bTraceDotColor,SIGNAL(clicked()),this,SLOT(untransforemdTraceDotColor()));
    connect(bMeasurementPointColor,SIGNAL(clicked()),this,SLOT(untransformedMeasurementPointColor()));

    connect(ePalatronBoxColor,SIGNAL(clicked()),this,SLOT(palatronBoxColor()));
    connect(ePalatronDotColor,SIGNAL(clicked()),this,SLOT(palatronDotColor()));

    connect(eTransformedAbstractBg,SIGNAL(clicked()),this,SLOT(transformedBackground()));
    connect(eTransformedMeasurementPoint,SIGNAL(clicked()),this,SLOT(transformedMeasurementPointColor()));
    connect(eTransformedTraceDot,SIGNAL(clicked()),this,SLOT(transforemdTraceDotColor()));
    connect(eTransformedTraceLine,SIGNAL(clicked()),this,SLOT(transformedTraceLineColor()));
    connect(eTransformedPalatronDot,SIGNAL(clicked()),this,SLOT(transformedPalatronDotColor()));
    connect(eFan,SIGNAL(clicked()),this,SLOT(fanColor()));

    connect(eTraceLineWidth,SIGNAL(valueChanged(int)),this,SLOT(untransformedTraceLineWidth(int)));
    connect(eTraceDotSize,SIGNAL(valueChanged(int)),this,SLOT(untransforemdTraceDotWidth(int)));

    connect(eMeasurementPointSize,SIGNAL(valueChanged(int)),this,SLOT(untransformedMeasurementPointWidth(int)));
    connect(ePalatronBoxWidth,SIGNAL(valueChanged(int)),this,SLOT(palatronBoxWidth(int)));
    connect(ePalatronDotSize,SIGNAL(valueChanged(int)),this,SLOT(palatronDotWidth(int)));

    this->setLayout(vertical);
}

void DisplaySettingsWidget::untransformedTraceLineColor()
{
    QColorDialog dlg(experiment->ds->cTraceLine);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTraceLine = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::untransforemdTraceDotColor()
{
    QColorDialog dlg(experiment->ds->cTraceDot);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTraceDot = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::untransformedMeasurementPointColor()
{
    QColorDialog dlg(experiment->ds->cMeasurementPoint);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cMeasurementPoint = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::palatronDotColor()
{
    QColorDialog dlg(experiment->ds->cPalatronDot);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cPalatronDot = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::palatronBoxColor()
{
    QColorDialog dlg(experiment->ds->cPalatronBox);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cPalatronBox = dlg.selectedColor();
    }
    emit updateParameters();
}


void DisplaySettingsWidget::transformedBackground()
{
    QColorDialog dlg(experiment->ds->cTransformedAbstractBg);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTransformedAbstractBg = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::transformedTraceLineColor()
{
    QColorDialog dlg(experiment->ds->cTransformedTraceLine);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTransformedTraceLine = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::transforemdTraceDotColor()
{
    QColorDialog dlg(experiment->ds->cTransformedTraceDot);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTransformedTraceDot = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::transformedMeasurementPointColor()
{
    QColorDialog dlg(experiment->ds->cTransformedMeasurementPoint);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTransformedMeasurementPoint = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::transformedPalatronDotColor()
{
    QColorDialog dlg(experiment->ds->cTransformedPalatronDot);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cTransformedPalatronDot = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::fanColor()
{
    QColorDialog dlg(experiment->ds->cFan);
    dlg.setOption(QColorDialog::ShowAlphaChannel);
    if( dlg.exec() )
    {
	experiment->ds->cFan = dlg.selectedColor();
    }
    emit updateParameters();
}

void DisplaySettingsWidget::untransformedTraceLineWidth(int size)
{
    experiment->ds->nTraceWidth = size;
    emit updateParameters();
}

void DisplaySettingsWidget::untransforemdTraceDotWidth(int size)
{
    experiment->ds->nTraceDotSize = size;
    emit updateParameters();
}

void DisplaySettingsWidget::untransformedMeasurementPointWidth(int size)
{
    experiment->ds->nMeasurementPointSize = size;
    emit updateParameters();
}

void DisplaySettingsWidget::palatronDotWidth(int size)
{
    experiment->ds->nPalatronDotSize = size;
    emit updateParameters();
}

void DisplaySettingsWidget::palatronBoxWidth(int size)
{
    experiment->ds->nPalatronBoxWidth = size;
    emit updateParameters();
}

