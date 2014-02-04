#include "experiment.h"
#include "session.h"
#include "subject.h"
#include "image.h"
#include "defaultsettings.h"

#include <QtDebug>
#include <QLine>
#include <QXmlStreamWriter>
#include <QVector2D>
#include <math.h>
#include <QFile>
#include <QXmlStreamReader>
#include <QInputDialog>
#include <QString>
#include <QFileInfo>

Experiment::Experiment()
{
    ds = new DefaultSettings;

    currentFilename = "";

    /*
    addSubject("Subject 1");
    addSubject("Subject 2");
    addSubject("Subject 3");
*/
    tracerName = "";

    lFanLeft = new QLine(-1,-1,-1,-1);
    lFanRight = new QLine(-1,-1,-1,-1);
    nFanLines = 10;
}

Experiment::~Experiment()
{
    delete lFanLeft;
    delete lFanRight;
}

void Experiment::addSubject(QString name)
{
    aSubjects << new Subject(name,this);

}

void Experiment::setName(QString name)
{
    sName = name;
}

void Experiment::setDescription(QString description)
{
    sDescription = description;
}

QString Experiment::name()
{
    return sName;
}

QString Experiment::description()
{
    return sDescription;
}

void Experiment::setTraceInterpretations(QStringList newdata)
{
    aTraceInterpretations = newdata;
    aTraceLocations.clear();
    for(int i=0; i< aTraceInterpretations.length(); i++)
    {
	aTraceLocations << Experiment::Ultrasound;
	aTraceTypes << Experiment::Grid;
    }
}

QStringList* Experiment::getTraceInterpretations()
{
    return &aTraceInterpretations;
}

void Experiment::setPointInterpretations(QStringList newdata)
{
    aPointInterpretations = newdata;
    aPointLocations.clear();
    for(int i=0; i< aPointInterpretations.length(); i++)
    {
	aPointLocations << Experiment::Video;
    }
}

QStringList* Experiment::getPointInterpretations()
{
    return &aPointInterpretations;
}

void Experiment::setSubjectDataInterpretations(QStringList newdata)
{
    aSubjectDataInterpretations = newdata;
    for(int i=0; i<aSubjects.length(); i++)
    {
	aSubjects[i]->setSubjectDataSize(aSubjectDataInterpretations.length());
    }
}

QStringList* Experiment::getSubjectDataInterpretations()
{
    return &aSubjectDataInterpretations;
}

void Experiment::setSessionDataInterpretations(QStringList newdata)
{
    aSessionDataInterpretations = newdata;

    for(int i=0; i<aSubjects.length(); i++)
    {
	for( int j=0; j<aSubjects.at(i)->sessions()->length(); j++ )
	    aSubjects.at(i)->sessions()->at(j)->setSessionDataSize(aSessionDataInterpretations.length());
    }

}

QStringList* Experiment::getSessionDataInterpretations()
{
    return &aSessionDataInterpretations;
}

bool Experiment::validSubject(int subject)
{
    if(subject < 0 || subject >= aSubjects.length() )
	return false;
    else
	return true;
}

bool Experiment::validSession(int subject, int session)
{
    if(subject < 0 || subject >= aSubjects.length() || session < 0 || session >= aSubjects.at(subject)->sessions()->length() )
	return false;
    else
	return true;
}

bool Experiment::validImage(int subject, int session, int image)
{
    if(subject < 0 || subject >= aSubjects.length() || session < 0 || session >= aSubjects.at(subject)->sessions()->length() || image < 0 || image >= aSubjects.at(subject)->sessions()->at(session)->images()->length() )
	return false;
    else
	return true;

}

void Experiment::setTraceLocation(int index, Experiment::Location loc)
{
    if(index>-1 && index < aTraceLocations.length() )
    {
	aTraceLocations[index] = loc;
    }
}

void Experiment::setPointLocation(int index, Experiment::Location loc)
{
    if(index>-1 && index < aPointLocations.length() )
    {
	aPointLocations[index] = loc;
    }
}

Experiment::Location Experiment::getPointLocation(int index)
{
    if(index>-1 && index < aPointLocations.length() )
    {
	return aPointLocations.at(index);
    }
    return Experiment::Error;
}

Experiment::Location Experiment::getTraceLocation(int index)
{
    if(index>-1 && index < aTraceLocations.length() )
    {
	return aTraceLocations.at(index);
    }
    return Experiment::Error;
}

QList<Experiment::Location>* Experiment::getPointLocations()
{
    return &aPointLocations;
}

QList<Experiment::Location>* Experiment::getTraceLocations()
{
    return &aTraceLocations;
}

void Experiment::serialize(QString fn)
{
    currentFilename = fn;

    QFile file(fn);
    file.open(QFile::WriteOnly | QFile::Text);
    QXmlStreamWriter xmlstream(&file);
    int i;

    xmlstream.setAutoFormatting(true);
    xmlstream.writeStartDocument();
    xmlstream.setCodec("UTF-8");

    xmlstream.writeComment("Feel free to modify values *within* tags, but do not delete tags or move them around. Doing so will cause strange errors.");
    xmlstream.writeStartElement("experiment");

    xmlstream.writeTextElement("experimentName",sName);
    xmlstream.writeTextElement("experimentDescription",sDescription);
    xmlstream.writeTextElement("tracingAlgorithm",tracerName);


    xmlstream.writeStartElement("traceInterpretations");
    for(i=0; i<aTraceInterpretations.length(); i++)
    {
	xmlstream.writeStartElement("traceInterpretation");
	xmlstream.writeAttribute("id",QString::number(i));
	xmlstream.writeCharacters(aTraceInterpretations.at(i));
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("pointInterpretations");
    for(i=0; i<aPointInterpretations.length(); i++)
    {
	xmlstream.writeStartElement("pointInterpretation");
	xmlstream.writeAttribute("id",QString::number(i));
	xmlstream.writeCharacters(aPointInterpretations.at(i));
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("subjectDataInterpretations");
    for(i=0; i<aSubjectDataInterpretations.length(); i++)
    {
	xmlstream.writeStartElement("subjectDataInterpretation");
	xmlstream.writeAttribute("id",QString::number(i));
	xmlstream.writeCharacters(aSubjectDataInterpretations.at(i));
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("sessionDataInterpretations");
    for(i=0; i<aSessionDataInterpretations.length(); i++)
    {
	xmlstream.writeStartElement("sessionDataInterpretation");
	xmlstream.writeAttribute("id",QString::number(i));
	xmlstream.writeCharacters(aSessionDataInterpretations.at(i));
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("traceLocations");
    for(i=0; i<aTraceLocations.length(); i++)
    {
	xmlstream.writeStartElement("traceLocation");
	xmlstream.writeAttribute("id",QString::number(i));
	switch(aTraceLocations.at(i))
	{
 case Experiment::Ultrasound:
	    xmlstream.writeAttribute("location","ultrasound");
	    break;
 case Experiment::Video:
	    xmlstream.writeAttribute("location","video");
	    break;
 default:
	    xmlstream.writeAttribute("location","error");
	    break;
	}
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("pointLocations");
    for(i=0; i<aPointLocations.length(); i++)
    {
	xmlstream.writeStartElement("pointLocation");
	xmlstream.writeAttribute("id",QString::number(i));
	switch(aPointLocations.at(i))
	{
 case Experiment::Ultrasound:
	    xmlstream.writeAttribute("location","ultrasound");
	    break;
 case Experiment::Video:
	    xmlstream.writeAttribute("location","video");
	    break;
 default:
	    xmlstream.writeAttribute("location","error");
	    break;
	}
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("traceTypes");
    for(i=0; i<aTraceLocations.length(); i++)
    {
	xmlstream.writeStartElement("traceType");
	xmlstream.writeAttribute("id",QString::number(i));
	switch(aTraceTypes.at(i))
	{
 case Experiment::Free:
	    xmlstream.writeAttribute("type","free");
	    break;
 case Experiment::Grid:
	    xmlstream.writeAttribute("type","grid");
	    break;
 default:
	    xmlstream.writeAttribute("type","error");
	    break;
	}
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();


    xmlstream.writeStartElement("radialGrid");
    xmlstream.writeTextElement("numberOfFanLines",QString::number(nFanLines));
    xmlstream.writeComment("The spacial descriptors here are arbitrary; beginning from left-to-right or top-to-bottom doesn't really matter.");
    xmlstream.writeStartElement("left");
    xmlstream.writeEmptyElement("top");
    xmlstream.writeAttribute("x",QString::number(lFanLeft->p1().x()));
    xmlstream.writeAttribute("y",QString::number(lFanLeft->p1().y()));
    xmlstream.writeEmptyElement("bottom");
    xmlstream.writeAttribute("x",QString::number(lFanLeft->p2().x()));
    xmlstream.writeAttribute("y",QString::number(lFanLeft->p2().y()));
    xmlstream.writeEndElement();
    xmlstream.writeStartElement("right");
    xmlstream.writeEmptyElement("top");
    xmlstream.writeAttribute("x",QString::number(lFanRight->p1().x()));
    xmlstream.writeAttribute("y",QString::number(lFanRight->p1().y()));
    xmlstream.writeEmptyElement("bottom");
    xmlstream.writeAttribute("x",QString::number(lFanRight->p2().x()));
    xmlstream.writeAttribute("y",QString::number(lFanRight->p2().y()));
    xmlstream.writeEndElement();
    xmlstream.writeEndElement();

    xmlstream.writeStartElement("pluginSettings");
    for(i=0; i<aPluginSettingsLabels.length(); i++)
    {
	xmlstream.writeStartElement("pluginSetting");
	xmlstream.writeAttribute("name",aPluginSettingsLabels.at(i));
	xmlstream.writeCharacters(aPluginSettings.at(i));
	xmlstream.writeEndElement();
    }
    xmlstream.writeEndElement();

    ds->serialize(&xmlstream);

    xmlstream.writeStartElement("subjects");
    for(i=0; i<aSubjects.length(); i++)
    {
	aSubjects.at(i)->serialize(&xmlstream);
    }
    xmlstream.writeEndElement();

    xmlstream.writeEndDocument(); // experiment
}

QLine* Experiment::fanLeft()
{
    return lFanLeft;
}

QLine* Experiment::fanRight()
{
    return lFanRight;
}

int Experiment::fanLines()
{
    return nFanLines;
}

void Experiment::setFanLines(int l)
{
    nFanLines = l;
}

QList<QLine>* Experiment::grid()
{
    return &aGrid;
}

void Experiment::updateGrid()
{
    // http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=geometry2

    aGrid.clear();

    if( fanLeft()->p1() == QPoint(-1,-1) ) { return; }


    // 1 is the left line
    int a1 = fanLeft()->p2().y() - fanLeft()->p1().y();
    int b1 = fanLeft()->p1().x() - fanLeft()->p2().x();
    int c1 = a1*fanLeft()->p1().x() + b1*fanLeft()->p1().y();

    // 2 is the right line
    int a2 = fanRight()->p2().y() - fanRight()->p1().y();
    int b2 = fanRight()->p1().x() - fanRight()->p2().x();
    int c2 = a2*fanRight()->p1().x() + b2*fanRight()->p1().y();

    int det = a1*b2 - a2*b1;

    int i;
    int nLines = fanLines() + 2;
    int tmpX, tmpY;
    int tmpNearX, tmpNearY;

    if( det == 0 ) // lines are parallel
    {
	for(i=0; i< nLines; i++)
	{
	    // say, the top
	    tmpX = fanLeft()->p2().x() - ((double)i/(double)(nLines-1))*(fanLeft()->p2().x()-fanRight()->p2().x());
	    tmpY = fanLeft()->p2().y() - ((double)i/(double)(nLines-1))*(fanLeft()->p2().y()-fanRight()->p2().y());

	    // the bottom
	    tmpNearX = fanLeft()->p1().x() - ((double)i/(double)(nLines-1))*(fanLeft()->p1().x()-fanRight()->p1().x());
	    tmpNearY = fanLeft()->p1().y() - ((double)i/(double)(nLines-1))*(fanLeft()->p1().y()-fanRight()->p1().y());

	    aGrid << QLine( tmpNearX, tmpNearY, tmpX, tmpY );
	}
    }
    else
    {
	int xint = (double)(b2*c1 - b1*c2) / (double)det;
	int yint = (double)(a1*c2 - a2*c1) / (double)det;

	// intersection = A
	// top of left fan = B
	// top of right fan = C
	QVector2D A(xint,yint);
	QVector2D B(fanLeft()->p1());
	QVector2D C(fanRight()->p1());
	QVector2D D(fanLeft()->p2());
	QVector2D E(fanRight()->p2());

	QVector2D AB = B - A;
	QVector2D AC = C - A;
	QVector2D AD = D - A;
	QVector2D AE = E - A;

	// flip horizontal
	AB.setY(AB.y()*-1);
	AC.setY(AC.y()*-1);

	double angle_AB_horizontal = atan2( AB.y() , AB.x() );
	double angle_AC_horizontal = atan2( AC.y() , AC.x() );
	double linelength = qMax( AB.length() , AC.length() );
	double nearlength = qMin( AD.length() , AE.length() );


	double tmpAngle;

	i=0;
	tmpAngle = angle_AC_horizontal + ((double)i/(double)(nLines-1))*(angle_AB_horizontal-angle_AC_horizontal);
	tmpNearX = xint - (int)round(nearlength * cos( tmpAngle ));
	tmpNearY = yint - (int)round(nearlength * sin( tmpAngle ));

	for(i=0; i< nLines; i++)
	{
	    tmpAngle = angle_AC_horizontal + ((double)i/(double)(nLines-1))*(angle_AB_horizontal-angle_AC_horizontal);
	    tmpX = xint + (int)round(linelength * cos( tmpAngle ));
	    tmpY = yint - (int)round(linelength * sin( tmpAngle ));

	    tmpNearX = xint + (int)round(nearlength * cos( tmpAngle ));
	    tmpNearY = yint - (int)round(nearlength * sin( tmpAngle ));

	    aGrid << QLine( tmpNearX, tmpNearY, tmpX, tmpY );
	}
    }
}

QList<Experiment::TraceType>* Experiment::getTraceTypes()
{
    return &aTraceTypes;
}

void Experiment::setTraceType(int index, Experiment::TraceType loc)
{
    if(index>-1 && index<aTraceTypes.length() && aTraceTypes[index] != loc)
    {
	aTraceTypes[index] = loc;
	if(aTraceTypes[index] == Experiment::Grid)
	{
	    for(int i=0; i<aSubjects.length(); i++)
	    {
		for(int j=0; j<aSubjects.at(i)->sessions()->length(); j++)
		{
		    for(int k=0; k < aSubjects.at(i)->sessions()->at(j)->images()->length(); k++)
		    {
			aSubjects.at(i)->sessions()->at(j)->images()->at(k)->traces()->at(index)->points()->clear();
			aSubjects.at(i)->sessions()->at(j)->images()->at(k)->traces()->at(index)->pointsTransformed()->clear();
		    }
		}
	    }
	}
    }
}

Experiment::TraceType Experiment::getTraceType(int index)
{
    if(index>-1 && index<aTraceTypes.length())
    {
	return aTraceTypes[index];
    }
    return Experiment::ErrorTraceType;
}

bool Experiment::readFromFile(QString fn)
{
    QFile file(fn);
    if(! file.open(QFile::ReadOnly | QFile::Text) ) { return false; }

    currentFilename = fn;

    QXmlStreamReader xml(&file);
    QString name, tmp;
    QXmlStreamAttributes attr;
    int i;

    while (!xml.atEnd()) {
	if(xml.readNext() == QXmlStreamReader::StartElement)
	{
	    name = xml.name().toString();

//	    qDebug() << name;
	    if(name == "experimentName") {
		this->setName(xml.readElementText());
	    }
	    else if(name == "experimentDescription") {
		this->setDescription(xml.readElementText());
	    }
	    else if(name == "tracingAlgorithm") {
		this->setTracer(xml.readElementText());
	    }
	    else if(name == "traceInterpretation") {
		aTraceInterpretations << xml.readElementText();
	    }
	    else if(name == "pointInterpretation") {
		aPointInterpretations << xml.readElementText();
	    }
	    else if(name == "subjectDataInterpretation") {
		aSubjectDataInterpretations << xml.readElementText();
	    }
	    else if(name == "sessionDataInterpretation") {
		aSessionDataInterpretations << xml.readElementText();
	    }
	    else if(name == "traceLocation") {
		attr = xml.attributes();
		if(attr.hasAttribute("location"))
		{
		    tmp = attr.value("location").toString();
		    if( tmp == "video" )
		    {
			aTraceLocations << Experiment::Video;
		    }
		    else if (tmp == "ultrasound")
		    {
			aTraceLocations << Experiment::Ultrasound;
		    }
		    else
		    {
			aTraceLocations << Experiment::Error;
		    }
		}
		else
		{
		    aTraceLocations << Experiment::Error;
		    qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in traceLocation tag. No location attribute.";
		    return false;
		}
	    }
	    else if(name == "pointLocation") {
		attr = xml.attributes();
		if(attr.hasAttribute("location"))
		{
		    tmp = attr.value("location").toString();
		    if( tmp == "video" )
		    {
			aPointLocations << Experiment::Video;
		    }
		    else if (tmp == "ultrasound")
		    {
			aPointLocations << Experiment::Ultrasound;
		    }
		    else
		    {
			aPointLocations << Experiment::Error;
		    }
		}
		else
		{
		    aPointLocations << Experiment::Error;
		    qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in pointLocation tag. No location attribute.";
		    return false;
		}
	    }
	    else if(name == "traceType") {
		attr = xml.attributes();
		if(attr.hasAttribute("type"))
		{
		    tmp = attr.value("type").toString();
		    if( tmp == "free" )
		    {
			aTraceTypes << Experiment::Free;
		    }
		    else if (tmp == "grid")
		    {
			aTraceTypes << Experiment::Grid;
		    }
		    else
		    {
			aTraceTypes << Experiment::ErrorTraceType;
		    }
		}
		else
		{
		    aTraceTypes << Experiment::ErrorTraceType;
		    qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in traceType tag. No grid attribute.";
		    return false;
		}
	    }
	    else if(name == "numberOfFanLines") {
		nFanLines = xml.readElementText().toInt();
	    }
	    else if(name == "left") {
		// top
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "top" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in left tag. The top element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    lFanLeft->setP1(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in top tag. No x or y attribute."; return false; }

		// bottom
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottom" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in left tag. The bottom element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    lFanLeft->setP2(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in bottom tag. No x or y attribute."; return false; }
	    }
	    else if(name == "right") {
		// top
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "top" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in right tag. The top element is missing, or is in the wrong place. Instead I found " << xml.name(); }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    lFanRight->setP1(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in top tag. No x or y attribute."; return false; }

		// bottom
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottom" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in right tag. The bottom element is missing, or is in the wrong place. Instead I found " << xml.name(); }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    lFanRight->setP2(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in bottom tag. No x or y attribute."; return false; }
	    }
	    else if( name == "pluginSetting")
	    {
		attr = xml.attributes();
		if(attr.hasAttribute("name"))
		{
		    this->setPluginSettings(attr.value("name").toString(),xml.readElementText());
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in pluginSetting tag. No name attribute."; return false; }

	    }
	    else if(name == "subject") {
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "subjectName") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The subjectName element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		else { aSubjects << new Subject(xml.readElementText(),this); }
	    }
	    else if(name == "subjectData") {
		// subject data
		for(i=0; i<this->aSubjectDataInterpretations.length(); i++)
		{
		    while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		    if( xml.name() != "datum") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The datum element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		    aSubjects.last()->setSubjectData(i,xml.readElementText());
		}
	    }
	    else if(name == "session") {
		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "sessionName") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The sessionName element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		else { *(aSubjects.last()->sessions()) << new Session(xml.readElementText(),aSubjects.last()); }
	    }
	    else if(name == "subjectData") {
		for(i=0; i<this->aSessionDataInterpretations.length(); i++)
		{
		    while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		    if( xml.name() != "datum") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The datum element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		    aSubjects.last()->sessions()->last()->setSessionData(i,xml.readElementText());
		}
	    }
	    else if(name == "dotColor") {
		attr = xml.attributes();
		if(attr.hasAttribute("r") && attr.hasAttribute("g") && attr.hasAttribute("b"))
		{
		    aSubjects.last()->sessions()->last()->setDotColor(QColor( attr.value("r").toString().toInt() , attr.value("g").toString().toInt() , attr.value("b").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in dotColor tag. No r, g, or b attribute."; return false; }
	    }
	    else if(name == "palateImage") {
		attr = xml.attributes();
		if(attr.hasAttribute("filename") && attr.hasAttribute("transparency") )
		{
		    *(aSubjects.last()->sessions()->last()->palateImages()) << new Image( attr.value("filename").toString() , aSubjects.last()->sessions()->last() );
		    *(aSubjects.last()->sessions()->last()->palateTransparencies()) << attr.value("transparency").toString().toInt();
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in palateImage tag. No filename or transparency attribute."; return false; }
	    }
	    else if(name == "palateTrace") {
		while( !(xml.readNext() == QXmlStreamReader::EndElement && xml.name() == "palateTrace") )
		{
		    if ( xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "point" )
		    {
			attr = xml.attributes();
			if(attr.hasAttribute("x") && attr.hasAttribute("y"))
			{
			    aSubjects.last()->sessions()->last()->addToPalateTrace( QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ) );
			    //				*(aSubjects.last()->sessions()->last()->images()->last()->traces()->last()->points()) << new QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() );
			}
			else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in point tag. No x or y attribute."; return false; }
		    }
		}
	    }
	    else if(name == "palateFromSession") {
		aSubjects.last()->sessions()->last()->setPalateFromSession(xml.readElementText().toInt());
	    }
	    else if(name == "palatronSettingsFromSession") {
		aSubjects.last()->sessions()->last()->setPalatronSettingsFromSession(xml.readElementText().toInt());
	    }
	    else if(name == "palatronBoxLocations") {
		// upperLeft //////////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "upperLeft") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The upperLeft element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "topLeftCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The topLeftCorner element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ul()->setTopLeft(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in topLeftCorner tag. No x or y attribute."; return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottomRightCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The bottomRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ul()->setBottomRight(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in bottomRightCorner tag. No x or y attribute."; return false; }

		// upperRight //////////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "upperRight") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The upperRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "topLeftCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The topLeftCorner element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ur()->setTopLeft(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in topLeftCorner tag. No x or y attribute."; return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottomRightCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The bottomRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ur()->setBottomRight(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in bottomRightCorner tag. No x or y attribute."; return false; }

		// lowerLeft //////////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "lowerLeft") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The lowerLeft element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "topLeftCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The topLeftCorner element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ll()->setTopLeft(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in topLeftCorner tag. No x or y attribute."; return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottomRightCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The bottomRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->ll()->setBottomRight(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in bottomRightCorner tag. No x or y attribute."; return false; }

		// lowerRight //////////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "lowerRight") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The lowerRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "topLeftCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The topLeftCorner element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->lr()->setTopLeft(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in topLeftCorner tag. No x or y attribute."; return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) {}
		if( xml.name() != "bottomRightCorner") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The bottomRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->lr()->setBottomRight(QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() ));
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " <<"Error in bottomRightCorner tag. No x or y attribute."; return false; }
		/*
		    qDebug() << *(aSubjects.last()->sessions()->last()->ul());
		    qDebug() << *(aSubjects.last()->sessions()->last()->ur());
		    qDebug() << *(aSubjects.last()->sessions()->last()->ll());
		    qDebug() << *(aSubjects.last()->sessions()->last()->lr());
*/
	    }
	    else if(name == "dotColorTolerance") {
		aSubjects.last()->sessions()->last()->setTolerance(xml.readElementText().toInt());
	    }
	    else if(name == "image") {
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "filename") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " <<"The filename element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		*(aSubjects.last()->sessions()->last()->images()) << new Image(xml.readElementText(), aSubjects.last()->sessions()->last() );


		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "interlacing") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " <<"The interlacing element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }

		QString tmp = xml.readElementText();
		if(tmp=="even")
		{
		    aSubjects.last()->sessions()->last()->images()->last()->setInterlacing(Image::EvenRows);
		}
		else if(tmp=="odd")
		{
		    aSubjects.last()->sessions()->last()->images()->last()->setInterlacing(Image::OddRows);
		}
		else if(tmp=="none")
		{
		    aSubjects.last()->sessions()->last()->images()->last()->setInterlacing(Image::NoInterlacing);
		}
	    }
	    else if(name == "dots") {
		// upperLeft ////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "upperLeft") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The upperLeft element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y") && attr.hasAttribute("manuallySpecified"))
		{
		    aSubjects.last()->sessions()->last()->images()->last()->ul()->setX(attr.value("x").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->ul()->setY(attr.value("y").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->setMul(attr.value("manuallySpecified").toString().toInt());
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in upperLeft tag. No x or y or manuallySpecified attribute."; return false; }

		// upperRight ////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "upperRight") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The upperRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y") && attr.hasAttribute("manuallySpecified"))
		{
		    aSubjects.last()->sessions()->last()->images()->last()->ur()->setX(attr.value("x").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->ur()->setY(attr.value("y").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->setMur(attr.value("manuallySpecified").toString().toInt());
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in upperRight tag. No x or y or manuallySpecified attribute."; return false; }

		// lowerLeft ////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "lowerLeft") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The lowerLeft element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y") && attr.hasAttribute("manuallySpecified"))
		{
		    aSubjects.last()->sessions()->last()->images()->last()->ll()->setX(attr.value("x").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->ll()->setY(attr.value("y").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->setMll(attr.value("manuallySpecified").toString().toInt());
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in lowerLeft tag. No x or y or manuallySpecified attribute."; return false; }

		// lowerRight ////////
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "lowerRight") { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "The lowerRight element is missing, or is in the wrong place. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y") && attr.hasAttribute("manuallySpecified"))
		{
		    aSubjects.last()->sessions()->last()->images()->last()->lr()->setX(attr.value("x").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->lr()->setY(attr.value("y").toString().toInt());
		    aSubjects.last()->sessions()->last()->images()->last()->setMlr(attr.value("manuallySpecified").toString().toInt());
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in lowerRight tag. No x or y or manuallySpecified attribute."; return false; }
	    }
	    else if(name == "trace") {
		*(aSubjects.last()->sessions()->last()->images()->last()->traces()) << new Trace;

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "untransformed" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "An untransformed tag was expected here. Instead I found " << xml.name(); return false; }
		while( !(xml.readNext() == QXmlStreamReader::EndElement && xml.name() == "untransformed") )
		{
		    if ( xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "point" )
		    {
			attr = xml.attributes();
			if(attr.hasAttribute("x") && attr.hasAttribute("y"))
			{
			    *(aSubjects.last()->sessions()->last()->images()->last()->traces()->last()->points()) << new QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() );
			}
			else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in point tag. No x or y attribute."; return false; }
		    }
		}

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "transformed" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "An transformed tag was expected here. Instead I found " << xml.name(); return false; }
		while( !(xml.readNext() == QXmlStreamReader::EndElement && xml.name() == "transformed") )
		{
		    if ( xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "point" )
		    {
			attr = xml.attributes();
			if(attr.hasAttribute("x") && attr.hasAttribute("y"))
			{
			    *(aSubjects.last()->sessions()->last()->images()->last()->traces()->last()->pointsTransformed()) << new QPoint( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() );
			}
			else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in point tag. No x or y attribute."; return false; }
		    }
		}
	    }
	    else if(name == "measurementPoint") {
		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "untransformed" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "An untransformed tag was expected here. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    *(aSubjects.last()->sessions()->last()->images()->last()->points()) << new Point( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() );
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in untransformed tag. No x or y attribute."; return false; }

		while( xml.readNext() != QXmlStreamReader::StartElement ) { }
		if( xml.name() != "transformed" ) { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "A transformed tag was expected here. Instead I found " << xml.name(); return false; }
		attr = xml.attributes();
		if(attr.hasAttribute("x") && attr.hasAttribute("y"))
		{
		    aSubjects.last()->sessions()->last()->images()->last()->points()->last()->setPointTransformed( attr.value("x").toString().toInt() , attr.value("y").toString().toInt() );
		}
		else { qDebug() << "Line " << xml.lineNumber() << ", Column " << xml.columnNumber() << ": " << "Error in transformed tag. No x or y attribute."; return false; }
	    }
	    else if(name == "defaultSettings") {
		ds->readTags(&xml);
	    }
	    else if(name == "palatronParameters") {
		aSubjects.last()->sessions()->last()->palatronSettings.readTags(&xml);
	    }
	}
    }

    if (xml.hasError()) {
	qDebug() << xml.errorString();
	return false;
    }

    file.close();

    updateGrid();

    //    qDebug() << this->ds->nTraceDotSize << this->ds->nTraceWidth;

    return true;
}

QString Experiment::tracer()
{
    return tracerName;
}

void Experiment::setTracer(QString name)
{
    tracerName = name;
}

void Experiment::setPluginSettings(QString label, QString xml)
{
    int index = aPluginSettingsLabels.indexOf(label);
    if(index == -1)
    {
	aPluginSettingsLabels << label;
	aPluginSettings << xml;
    }
    else
    {
	aPluginSettings[index] = xml;
    }
}

bool Experiment::hasPluginSettings(QString label)
{
    if( aPluginSettingsLabels.indexOf(label) == -1)
    {
	return false;
    }
    else
    {
	return true;
    }
}

QString Experiment::pluginSettings(QString label)
{
    int index = aPluginSettingsLabels.indexOf(label);
    if(index == -1)
    {
	return "";
    }
    else
    {
	return aPluginSettings.at(index);
    }
}

void Experiment::addSessionFromTabDelimitedFile(QString filename, QString sSubject, QString sSession)
{
    QFile file(filename);
    if(! file.open(QFile::ReadOnly | QFile::Text) ) { return; }

    QFileInfo info(file);
    QString directory = info.canonicalPath() + "/";

    Subject* subj;

    bool existing = false;
    for(int i=0; i<aSubjects.count(); i++)
    {
	if( aSubjects.at(i)->name() == sSubject )
	{
	    existing = true;
	    subj = aSubjects.at(i);
	}
    }
    if(!existing)
    {
	subj = new Subject(sSubject,this);
	aSubjects << subj;
    }

    Session* session = new Session(sSession,subj);
    *(subj->sessions()) << session;

    QTextStream in(&file);
    int ct=0;
    while (!in.atEnd())
    {
	QString line = in.readLine();
	ct++;
	QStringList items = line.split("\t");
	if( items.count() != 93 )
	{
	    qDebug() << "There are not 93 items on line " << ct;
	    return;
	}

	if(items.at(0)=="Filename") { continue; }

	Image *img = new Image(directory+items.at(0), session);
	*(session->images()) << img;

	Trace *tr = new Trace;
	*(img->traces()) << tr;
	for(int i=1; i<=64; i+=2)
	{
	    int x = items.at(i).toInt();
	    int y = items.at(i+1).toInt();
	    if( x != -1 && y != -1 )
	    {
		*(tr->points()) << new QPoint(x,y);
	    }
	}
	img->setMul(true);
	img->setMur(true);
	img->setMll(true);
	img->setMlr(true);
	*(img->ul()) = QPoint(items.at(65).toInt(),items.at(66).toInt());
	*(img->ur()) = QPoint(items.at(67).toInt(),items.at(68).toInt());
	*(img->ll()) = QPoint(items.at(69).toInt(),items.at(70).toInt());
	*(img->lr()) = QPoint(items.at(71).toInt(),items.at(72).toInt());

	int counter=0;
	for(int i=73; i<=92; i+=2)
	{
	    while( !(img->points()->count() > counter ) )
		*(img->points()) << new Point(-1,-1);
	    int x = items.at(i).toInt();
	    int y = items.at(i+1).toInt();
	    img->setPoint(counter, QPoint(x,y) );
	}
    }
}
