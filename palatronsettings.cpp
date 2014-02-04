#include "palatronsettings.h"

#include <QtDebug>
#include <QXmlStreamReader>

PalatronSettings::PalatronSettings()
{
    // palatron settings
    OverlayX = 0;
    OverlayY = 0;
    Angle = 0.0;
    UsScale = 0.23856000602245331;
    tranlrmm = 250.0;
    ortranrmm = 314.0;
    ortranlmm = 72.5;
    usoriginx = 390;
    usoriginy = 416;
    vertical_distortion_correction = (double)533/(double)480;
    horizontal_distortion_correction = 1.0;

    faceLocation = 150;

    colorToleranceMinimum = 0;
    colorToleranceMaximum = 440;
    colorToleranceDefault = 140;
}


bool PalatronSettings::readTags(QXmlStreamReader *xml)
{
    QString name;
    QXmlStreamAttributes attr;

//    qDebug() << this->nTraceDotSize << this->nTraceWidth;

    while( !( xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "palatronParameters" ) ) {
	if(xml->readNext() == QXmlStreamReader::StartElement)
	{
	    name = xml->name().toString();
	    if(name == "OverlayX") {
		OverlayX = xml->readElementText().toInt();
	    }
	    else if(name == "OverlayY") {
		OverlayY = xml->readElementText().toInt();
	    }
	    else if(name == "Angle") {
		Angle = xml->readElementText().toDouble();
	    }
	    else if(name == "UsScale") {
		UsScale = xml->readElementText().toDouble();
	    }
	    else if(name == "tranlrmm") {
		tranlrmm = xml->readElementText().toDouble();
	    }
	    else if(name == "ortranrmm") {
		ortranrmm = xml->readElementText().toDouble();
	    }
	    else if(name == "ortranlmm") {
		ortranlmm = xml->readElementText().toDouble();
	    }
	    else if(name == "usoriginx") {
		usoriginx = xml->readElementText().toDouble();
	    }
	    else if(name == "usoriginy") {
		usoriginy = xml->readElementText().toDouble();
	    }
	    else if(name == "vertical_distortion_correction") {
		vertical_distortion_correction = xml->readElementText().toDouble();
	    }
	    else if(name == "horizontal_distortion_correction") {
		horizontal_distortion_correction = xml->readElementText().toDouble();
	    }
	    else if(name == "faceLocation") {
		faceLocation = xml->readElementText().toInt();
	    }
	}
    }

    if (xml->hasError()) {
	qDebug() << xml->errorString();
	return false;
    }

    return true;
}
