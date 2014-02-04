#include "defaultsettings.h"

#include <QColor>
#include <QFile>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <QtDebug>

DefaultSettings::DefaultSettings()
{
    if( readFromFile() )
    {
	return; // settings file is available
    }

    // display settings
    cTraceLine = QColor(255,255,0);
    cMeasurementPoint = QColor(0,0,255);

    cPalatronBox = QColor(0,0,255);
    nPalatronBoxWidth = 1;

    cPalatronDot = QColor(255,255,0);
    nPalatronDotSize = 3;

    cTraceDot = QColor(255,0,0);
    nTraceDotSize = 2;

    cTransformedAbstractBg = QColor(0,0,0);
    cTransformedTraceLine = QColor(255,255,0);
    cTransformedTraceDot = QColor(255,0,0);
    cTransformedPalatronDot = QColor(255,255,0);

    cFan = QColor(255,255,0,128);

    nMeasurementPointSize = 3;
    nTraceWidth = 1;

    nGridLines = 10;
    nMaxGridLines = 150;
/*
    // palatron settings
    OverlayX = 0;
    OverlayY = 0;
    Angle = 0.0;
    UsScale = 0.23856000602245331;
    tranlrmm = 250.0;
    ortranrmm = 314.0;
    ortranlmm = 72.5;
//    imagecenterx = 360.5;
//    imagecentery = 266.5;
    usoriginx = 390;
    usoriginy = 416;
    vertical_distortion_correction = (double)533/(double)480;
    horizontal_distortion_correction = 1.0;

    faceLocation = 150;
*/
    colorToleranceMinimum = 0;
    colorToleranceMaximum = 440;
    colorToleranceDefault = 140;

    // NEEDS TO BE SERIALIZED
    defaultPalateTransparency = 20;

    writeToFile(); // create a settings file with these default values
}

bool DefaultSettings::readFromFile()
{
    QFile file("defaultsettings.xml");
    if(! file.open(QFile::ReadOnly | QFile::Text) ) { qDebug() << "Could not open a default settings file."; return false; }

    QXmlStreamReader xml(&file);

    return readTags(&xml);
}

void DefaultSettings::writeToFile()
{
    QFile file("defaultsettings.xml");
    if(! file.open(QFile::WriteOnly | QFile::Text) ) { qDebug() << "Could not open default settings file for writing. Exiting."; return; }
    QXmlStreamWriter xmlstream(&file);

    xmlstream.setAutoFormatting(true);
    xmlstream.writeStartDocument();

    serialize(&xmlstream);

    xmlstream.writeEndDocument(); // defaultSettings

    return;
}

void DefaultSettings::serialize(QXmlStreamWriter *xmlstream)
{
    xmlstream->writeStartElement("defaultSettings");

    xmlstream->writeStartElement("displaySettings");

    xmlstream->writeStartElement("untransformedDisplaySettings");

    xmlstream->writeStartElement("traceSettings");

    xmlstream->writeEmptyElement("traceLineColor");
    xmlstream->writeAttribute("r", QString::number(cTraceLine.red()));
    xmlstream->writeAttribute("g", QString::number(cTraceLine.green()));
    xmlstream->writeAttribute("b", QString::number(cTraceLine.blue()));
    xmlstream->writeAttribute("a", QString::number(cTraceLine.alpha()));

    xmlstream->writeTextElement("traceLineWidthInPixels",QString::number(nTraceWidth));

    xmlstream->writeEmptyElement("tracingDotColor");
    xmlstream->writeAttribute("r", QString::number(cTraceDot.red()));
    xmlstream->writeAttribute("g", QString::number(cTraceDot.green()));
    xmlstream->writeAttribute("b", QString::number(cTraceDot.blue()));
    xmlstream->writeAttribute("a", QString::number(cTraceDot.alpha()));

    xmlstream->writeTextElement("tracingDotWidthInPixels",QString::number(nTraceDotSize));

    xmlstream->writeEndElement(); // traceSettings

    xmlstream->writeStartElement("measurementPointSettings");

    xmlstream->writeEmptyElement("measurementPointColor");
    xmlstream->writeAttribute("r", QString::number(cMeasurementPoint.red()));
    xmlstream->writeAttribute("g", QString::number(cMeasurementPoint.green()));
    xmlstream->writeAttribute("b", QString::number(cMeasurementPoint.blue()));
    xmlstream->writeAttribute("a", QString::number(cMeasurementPoint.alpha()));

    xmlstream->writeTextElement("measurementPointWidthInPixels",QString::number(nMeasurementPointSize));

    xmlstream->writeEndElement(); // measurementPointSettings

    xmlstream->writeEndElement(); // untransformedDisplaySettings


    xmlstream->writeStartElement("transformedDisplaySettings");

    xmlstream->writeEmptyElement("transformedTraceLineColor");
    xmlstream->writeAttribute("r", QString::number(cTransformedTraceLine.red()));
    xmlstream->writeAttribute("g", QString::number(cTransformedTraceLine.green()));
    xmlstream->writeAttribute("b", QString::number(cTransformedTraceLine.blue()));
    xmlstream->writeAttribute("a", QString::number(cTransformedTraceLine.alpha()));

    xmlstream->writeEmptyElement("transformedTracingDotColor");
    xmlstream->writeAttribute("r", QString::number(cTransformedTraceDot.red()));
    xmlstream->writeAttribute("g", QString::number(cTransformedTraceDot.green()));
    xmlstream->writeAttribute("b", QString::number(cTransformedTraceDot.blue()));
    xmlstream->writeAttribute("a", QString::number(cTransformedTraceDot.alpha()));

    xmlstream->writeEmptyElement("transformedMeasurementPointColor");
    xmlstream->writeAttribute("r", QString::number(cTransformedMeasurementPoint.red()));
    xmlstream->writeAttribute("g", QString::number(cTransformedMeasurementPoint.green()));
    xmlstream->writeAttribute("b", QString::number(cTransformedMeasurementPoint.blue()));
    xmlstream->writeAttribute("a", QString::number(cTransformedMeasurementPoint.alpha()));

    xmlstream->writeEmptyElement("transformedPalatronDotColor");
    xmlstream->writeAttribute("r", QString::number(cTransformedPalatronDot.red()));
    xmlstream->writeAttribute("g", QString::number(cTransformedPalatronDot.green()));
    xmlstream->writeAttribute("b", QString::number(cTransformedPalatronDot.blue()));
    xmlstream->writeAttribute("a", QString::number(cTransformedPalatronDot.alpha()));

    xmlstream->writeEmptyElement("transformedBackgroundColor");
    xmlstream->writeAttribute("r", QString::number(cTransformedAbstractBg.red()));
    xmlstream->writeAttribute("g", QString::number(cTransformedAbstractBg.green()));
    xmlstream->writeAttribute("b", QString::number(cTransformedAbstractBg.blue()));
    xmlstream->writeAttribute("a", QString::number(cTransformedAbstractBg.alpha()));

    xmlstream->writeEndElement(); // transformedDisplaySettings

    xmlstream->writeStartElement("palatronDisplaySettings");

    xmlstream->writeEmptyElement("palatronBoxColor");
    xmlstream->writeAttribute("r", QString::number(cPalatronBox.red()));
    xmlstream->writeAttribute("g", QString::number(cPalatronBox.green()));
    xmlstream->writeAttribute("b", QString::number(cPalatronBox.blue()));
    xmlstream->writeAttribute("a", QString::number(cPalatronBox.alpha()));

    xmlstream->writeTextElement("palatronBoxWidthInPixels",QString::number(nPalatronBoxWidth));

    xmlstream->writeEmptyElement("palatronDotColor");
    xmlstream->writeAttribute("r", QString::number(cPalatronDot.red()));
    xmlstream->writeAttribute("g", QString::number(cPalatronDot.green()));
    xmlstream->writeAttribute("b", QString::number(cPalatronDot.blue()));
    xmlstream->writeAttribute("a", QString::number(cPalatronDot.alpha()));

    xmlstream->writeTextElement("palatronDotWidthInPixels",QString::number(nPalatronDotSize));

    xmlstream->writeEndElement(); // palatronDisplaySettings

    xmlstream->writeEmptyElement("fanColor");
    xmlstream->writeAttribute("r", QString::number(cFan.red()));
    xmlstream->writeAttribute("g", QString::number(cFan.green()));
    xmlstream->writeAttribute("b", QString::number(cFan.blue()));
    xmlstream->writeAttribute("a", QString::number(cFan.alpha()));

    xmlstream->writeEndElement(); // displaySettings

    xmlstream->writeStartElement("palatronSettings");

    xmlstream->writeTextElement("defaultPalateTransparency",QString::number(defaultPalateTransparency));

    xmlstream->writeStartElement("gridlineSettings");
    xmlstream->writeTextElement("defaultNumberOfGridLines",QString::number(nGridLines));
    xmlstream->writeTextElement("maximumNumberOfGridLines",QString::number(nMaxGridLines));
    xmlstream->writeEndElement(); // gridlineSettings
/*
    xmlstream->writeStartElement("palatronParameters");
    xmlstream->writeTextElement("OverlayX",QString::number(OverlayX));
    xmlstream->writeTextElement("OverlayY",QString::number(OverlayY));
    xmlstream->writeTextElement("Angle",QString::number(Angle));
    xmlstream->writeTextElement("UsScale",QString::number(UsScale));
    xmlstream->writeTextElement("tranlrmm",QString::number(tranlrmm));
    xmlstream->writeTextElement("ortranrmm",QString::number(ortranrmm));
    xmlstream->writeTextElement("ortranlmm",QString::number(ortranlmm));
    xmlstream->writeTextElement("usoriginx",QString::number(usoriginx));
    xmlstream->writeTextElement("usoriginy",QString::number(usoriginy));
    xmlstream->writeTextElement("vertical_distortion_correction",QString::number(vertical_distortion_correction));
    xmlstream->writeTextElement("horizontal_distortion_correction",QString::number(horizontal_distortion_correction));
    xmlstream->writeTextElement("faceLocation",QString::number(faceLocation));
    xmlstream->writeEndElement(); // palatronParameters
*/
    xmlstream->writeStartElement("dotTrackingParameters");
    xmlstream->writeTextElement("defaultColorTolerance",QString::number(nGridLines));
    xmlstream->writeTextElement("minimumColorTolerance",QString::number(colorToleranceDefault));
    xmlstream->writeTextElement("maximumColorTolerance",QString::number(colorToleranceMaximum));
    xmlstream->writeEndElement(); // dotTrackingParameters

    xmlstream->writeEndElement(); // palatronSettings

    xmlstream->writeEndElement(); // defaultSettings
}

bool DefaultSettings::readTags(QXmlStreamReader *xml)
{
    QString name;
    QXmlStreamAttributes attr;

//    qDebug() << this->nTraceDotSize << this->nTraceWidth;

    while( !( xml->tokenType() == QXmlStreamReader::EndElement && xml->name() == "defaultSettings" ) ) {
	if(xml->readNext() == QXmlStreamReader::StartElement)
	{
	    name = xml->name().toString();
	    if(name == "traceLineColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTraceLine = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
//		    qDebug() << cTraceLine << attr.value("r").toString().toInt() << attr.value("g").toString().toInt() << attr.value("b").toString().toInt();
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in traceLineColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "traceLineWidthInPixels") {
		nTraceWidth = xml->readElementText().toInt();
//		qDebug() << nTraceWidth;
	    }
	    else if(name == "tracingDotColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTraceDot = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in tracingDotColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "tracingDotWidthInPixels") {
		nTraceDotSize = xml->readElementText().toInt();
	    }
	    else if(name == "measurementPointColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cMeasurementPoint = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "measurementPointWidthInPixels") {
		nMeasurementPointSize = xml->readElementText().toInt();
	    }
	    else if(name == "palatronBoxColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cPalatronBox = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "palatronBoxWidthInPixels") {
		nPalatronBoxWidth = xml->readElementText().toInt();
	    }
	    else if(name == "palatronDotColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cPalatronDot = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "palatronDotWidthInPixels") {
		nPalatronDotSize = xml->readElementText().toInt();
	    }
	    else if(name == "transformedBackgroundColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTransformedAbstractBg = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "transformedTraceLineColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTransformedTraceLine = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "transformedTracingDotColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTransformedTraceDot = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "transformedMeasurementPointColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTransformedMeasurementPoint = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "transformedPalatronDotColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cTransformedPalatronDot = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "fanColor") {
		attr = xml->attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b") && attr.hasAttribute("a"))
		{
		    cFan = QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() , attr.value("a").toString().toInt() );
		}
		else { qDebug() << "Line " << xml->lineNumber() << ", Column " << xml->columnNumber() << ": " << "Error in measurementPointColor tag. No r, g, b, or a attribute."; return false; }
	    }
	    else if(name == "defaultNumberOfGridLines") {
		nGridLines = xml->readElementText().toInt();
	    }
	    else if(name == "maximumNumberOfGridLines") {
		nMaxGridLines = xml->readElementText().toInt();
	    }
	    else if(name == "minimumColorTolerance") {
		colorToleranceMinimum = xml->readElementText().toInt();
	    }
	    else if(name == "maximumColorTolerance") {
		colorToleranceMaximum = xml->readElementText().toInt();
	    }
	    else if(name == "defaultColorTolerance") {
		colorToleranceDefault = xml->readElementText().toInt();
	    }
/*
	    else if(name == "OverlayX") {
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
*/
	    else if(name == "defaultPalateTransparency") {
		defaultPalateTransparency = xml->readElementText().toInt();
	    }
	}
    }

//    qDebug() << this->nTraceDotSize << this->nTraceWidth;

    if (xml->hasError()) {
	qDebug() << xml->errorString();
	return false;
    }

    return true;
}



