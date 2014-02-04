#ifndef PALATRONSETTINGS_H
#define PALATRONSETTINGS_H

class QXmlStreamReader;

class PalatronSettings
{
public:
    PalatronSettings();

    bool readTags(QXmlStreamReader *xml);

    //////////////////////
    // Palatron settings
    short OverlayX, OverlayY;
    double Angle, UsScale,tranlrmm,ortranrmm,ortranlmm;
    double usoriginx, usoriginy;
    double vertical_distortion_correction, horizontal_distortion_correction;
    int colorToleranceMinimum, colorToleranceMaximum, colorToleranceDefault;
    int faceLocation;
};

#endif // PALATRONSETTINGS_H
