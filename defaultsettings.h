#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <QColor>

class QXmlStreamWriter;
class QXmlStreamReader;


class DefaultSettings
{
public:
    DefaultSettings();
    ~DefaultSettings() {}


    bool readFromFile();
    void writeToFile();

    void serialize(QXmlStreamWriter *xmlstream);
    bool readTags(QXmlStreamReader *xml);

    //////////////////////
    // Display settings
    QColor cMeasurementPoint, cTraceLine, cTraceDot, cPalatronBox, cPalatronDot;
    int nMeasurementPointSize, nTraceWidth, nTraceDotSize, nPalatronBoxWidth, nPalatronDotSize;
    QColor cTransformedAbstractBg;
    QColor cTransformedMeasurementPoint, cTransformedTraceLine, cTransformedTraceDot, cTransformedPalatronDot;
    QColor cFan;

    int nGridLines, nMaxGridLines;

    int defaultPalateTransparency;

    int colorToleranceMinimum, colorToleranceMaximum, colorToleranceDefault;

    /*
    //////////////////////
    // Palatron settings
    short OverlayX, OverlayY;
    double Angle, UsScale,tranlrmm,ortranrmm,ortranlmm;
    double usoriginx, usoriginy;
    double vertical_distortion_correction, horizontal_distortion_correction;
    int faceLocation;
*/
    //////////////////////
};

#endif // DEFAULTSETTINGS_H
