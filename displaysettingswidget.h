#ifndef DISPLAYSETTINGSWIDGET_H
#define DISPLAYSETTINGSWIDGET_H

#include <QWidget>
#include <QDialog>

class Experiment;

class DisplaySettingsWidget : public QDialog
{
Q_OBJECT
public:
    DisplaySettingsWidget(Experiment *exp, QWidget *parent = 0);

    Experiment *experiment;

signals:
    void updateParameters();

public slots:
    void untransformedTraceLineColor();
    void untransforemdTraceDotColor();
    void untransformedMeasurementPointColor();

    void palatronDotColor();
    void palatronBoxColor();

    void transformedBackground();
    void transformedTraceLineColor();
    void transforemdTraceDotColor();
    void transformedMeasurementPointColor();
    void transformedPalatronDotColor();

    void fanColor();

    void untransformedTraceLineWidth(int size);
    void untransforemdTraceDotWidth(int size);
    void untransformedMeasurementPointWidth(int size);

    void palatronDotWidth(int size);
    void palatronBoxWidth(int size);
};

#endif // DISPLAYSETTINGSWIDGET_H
