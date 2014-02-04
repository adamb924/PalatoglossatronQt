#include "session.h"
#include "image.h"
#include "subject.h"

#include <QtDebug>
#include <QXmlStreamWriter>

Session::Session()
{

}

Session::~Session()
{
    qDeleteAll(aPalateImages.begin(), aPalateImages.end());
    qDeleteAll(aImages.begin(), aImages.end());
}

Session::Session(QString name, Subject *subj)
{
    subject = subj;

    sName = name;

//    nPalateInTrace = -1;

    cDotColor = QColor(255,149,224);
    nTolerance = 20;

    nPalateFromSession = -1;
    nPalatronSettingsFromSession = -1;

    rUL = QRect(-1,-1,0,0);
    rUR = QRect(-1,-1,0,0);
    rLL = QRect(-1,-1,0,0);
    rLR = QRect(-1,-1,0,0);

    /*
    aImages << new Image("C:\\Users\\Adam\\Documents\\QtWork\\PalatoglossatronQt\\maam1.jpg",2,3,this);
    aImages << new Image("C:\\Users\\Adam\\Documents\\QtWork\\PalatoglossatronQt\\maam2.jpg",2,3,this);
    aImages << new Image("C:\\Users\\Adam\\Documents\\QtWork\\PalatoglossatronQt\\maam3.jpg",2,3,this);
    aImages << new Image("C:\\Users\\Adam\\Documents\\QtWork\\PalatoglossatronQt\\maam4.jpg",2,3,this);
    aImages << new Image("C:\\Users\\Adam\\Documents\\QtWork\\PalatoglossatronQt\\maam5.jpg",2,3,this);
*/
}

QString Session::name()
{
    return sName;
}

QList<Image*>* Session::images()
{
    return &aImages;
}

QStringList* Session::sessionData()
{
    return &aSessionData;
}


void Session::setName(QString n)
{
    sName = n;
}

void Session::setSessionData(int index, QString data)
{
    if(index > -1)
    {
	if(index >= aSessionData.length())
	    setSessionDataSize(index);
	aSessionData[index] = data;
    }
}

void Session::setSessionDataSize(int size)
{
    while( aSessionData.length() <= size )
    {
	aSessionData << "";
    }
}

int Session::palateFromSession()
{
    return nPalateFromSession;
}

void Session::setPalateFromSession(int index)
{
    nPalateFromSession = index;
}

int Session::palatronSettingsFromSession()
{
    return nPalatronSettingsFromSession;
}

void Session::setPalatronSettingsFromSession(int index)
{
//    qDebug() << "Session::setPalatronSettingsFromSession" << index;
    nPalatronSettingsFromSession = index;
}

QRect* Session::ul()
{
    return &rUL;
}

QRect* Session::ur()
{
    return &rUR;
}

QRect* Session::ll()
{
    return &rLL;
}

QRect* Session::lr()
{
    return &rLR;
}

QColor Session::dotColor()
{
    return cDotColor;
}

void Session::setDotColor(QColor col)
{
/*
    for(int i=0; i<aImages.length(); i++)
    {
	aImages.at(i)->invalidateDotView();
    }
*/
    cDotColor = col;
//    qDebug() << "Setting to " << cDotColor.red() << cDotColor.green() << cDotColor.blue();
}

int Session::tolerance()
{
    return nTolerance;
}

void Session::setTolerance(int tol)
{
/*
    for(int i=0; i<aImages.length(); i++)
    {
	aImages.at(i)->invalidateDotView();
    }
*/
    nTolerance = tol;
}

void Session::serialize(QXmlStreamWriter *xmlstream)
{
    int i;

    xmlstream->writeStartElement("session");

    xmlstream->writeTextElement("sessionName",sName);

    xmlstream->writeStartElement("sessionData");
    for(i=0; i<aSessionData.length(); i++)
    {
	xmlstream->writeStartElement("datum");
	xmlstream->writeAttribute("id",QString::number(i));
	xmlstream->writeCharacters(aSessionData.at(i));
	xmlstream->writeEndElement(); // datum
    }
    xmlstream->writeEndElement(); // sessionData
/*
    Trace palateTrace;
    QList<Image*> aPalateImages;
    QList<int> aPalateTransparencies;
*/


    xmlstream->writeStartElement("palateData");

    xmlstream->writeStartElement("palateImages");

    for(i=0; i<aPalateImages.length(); i++)
    {
	xmlstream->writeEmptyElement("palateImage");
	xmlstream->writeAttribute("filename",aPalateImages.at(i)->filename());
	xmlstream->writeAttribute("transparency",QString::number(aPalateTransparencies.at(i)));
    }
    xmlstream->writeEndElement();

    xmlstream->writeStartElement("palateTrace");
    for(i=0; i<palateTrace.points()->count(); i++)
    {
	xmlstream->writeEmptyElement("point");
	xmlstream->writeAttribute("x", QString::number( palateTrace.points()->at(i)->x() ));
	xmlstream->writeAttribute("y", QString::number( palateTrace.points()->at(i)->y() ));
    }
    xmlstream->writeEndElement();

    xmlstream->writeEndElement();

    xmlstream->writeEmptyElement("dotColor");
    xmlstream->writeAttribute("r",QString::number(cDotColor.red()));
    xmlstream->writeAttribute("g",QString::number(cDotColor.green()));
    xmlstream->writeAttribute("b",QString::number(cDotColor.blue()));

    xmlstream->writeTextElement("palateFromSession",QString::number(nPalateFromSession));
    xmlstream->writeTextElement("palatronSettingsFromSession",QString::number(nPalatronSettingsFromSession));

    // write palatron settings
    xmlstream->writeStartElement("palatronParameters");
    xmlstream->writeTextElement("OverlayX",QString::number(palatronSettings.OverlayX));
    xmlstream->writeTextElement("OverlayY",QString::number(palatronSettings.OverlayY));
    xmlstream->writeTextElement("Angle",QString::number(palatronSettings.Angle));
    xmlstream->writeTextElement("UsScale",QString::number(palatronSettings.UsScale));
    xmlstream->writeTextElement("tranlrmm",QString::number(palatronSettings.tranlrmm));
    xmlstream->writeTextElement("ortranrmm",QString::number(palatronSettings.ortranrmm));
    xmlstream->writeTextElement("ortranlmm",QString::number(palatronSettings.ortranlmm));
    xmlstream->writeTextElement("usoriginx",QString::number(palatronSettings.usoriginx));
    xmlstream->writeTextElement("usoriginy",QString::number(palatronSettings.usoriginy));
    xmlstream->writeTextElement("vertical_distortion_correction",QString::number(palatronSettings.vertical_distortion_correction));
    xmlstream->writeTextElement("horizontal_distortion_correction",QString::number(palatronSettings.horizontal_distortion_correction));
    xmlstream->writeTextElement("faceLocation",QString::number(palatronSettings.faceLocation));
    xmlstream->writeEndElement(); // palatronParameters


    xmlstream->writeStartElement("palatronBoxLocations");

    xmlstream->writeStartElement("upperLeft");
    xmlstream->writeEmptyElement("topLeftCorner");
    xmlstream->writeAttribute("x",QString::number(rUL.topLeft().x()));
    xmlstream->writeAttribute("y",QString::number(rUL.topLeft().y()));
    xmlstream->writeEmptyElement("bottomRightCorner");
    xmlstream->writeAttribute("x",QString::number(rUL.bottomRight().x()));
    xmlstream->writeAttribute("y",QString::number(rUL.bottomRight().y()));
    xmlstream->writeEndElement();

    xmlstream->writeStartElement("upperRight");
    xmlstream->writeEmptyElement("topLeftCorner");
    xmlstream->writeAttribute("x",QString::number(rUR.topLeft().x()));
    xmlstream->writeAttribute("y",QString::number(rUR.topLeft().y()));
    xmlstream->writeEmptyElement("bottomRightCorner");
    xmlstream->writeAttribute("x",QString::number(rUR.bottomRight().x()));
    xmlstream->writeAttribute("y",QString::number(rUR.bottomRight().y()));
    xmlstream->writeEndElement();

    xmlstream->writeStartElement("lowerLeft");
    xmlstream->writeEmptyElement("topLeftCorner");
    xmlstream->writeAttribute("x",QString::number(rLL.topLeft().x()));
    xmlstream->writeAttribute("y",QString::number(rLL.topLeft().y()));
    xmlstream->writeEmptyElement("bottomRightCorner");
    xmlstream->writeAttribute("x",QString::number(rLL.bottomRight().x()));
    xmlstream->writeAttribute("y",QString::number(rLL.bottomRight().y()));
    xmlstream->writeEndElement();

    xmlstream->writeStartElement("lowerRight");
    xmlstream->writeEmptyElement("topLeftCorner");
    xmlstream->writeAttribute("x",QString::number(rLR.topLeft().x()));
    xmlstream->writeAttribute("y",QString::number(rLR.topLeft().y()));
    xmlstream->writeEmptyElement("bottomRightCorner");
    xmlstream->writeAttribute("x",QString::number(rLR.bottomRight().x()));
    xmlstream->writeAttribute("y",QString::number(rLR.bottomRight().y()));
    xmlstream->writeEndElement();

    xmlstream->writeEndElement(); // palatronBoxLocations

    xmlstream->writeTextElement("dotColorTolerance",QString::number(nTolerance));

/*
-    QColor cDotColor;
-    int nTolerance;

-    QString sName;
-    QStringList aSessionData;
-    QList<Image*> aImages;

-    bool nPalateFromSession;
-    bool nPalatronSettingsFromSession;

-    QRect rUL, rUR, rLL, rLR;
*/

    xmlstream->writeStartElement("images");
    for(i=0; i<aImages.length(); i++)
    {
	aImages.at(i)->serialize(xmlstream);
    }
    xmlstream->writeEndElement(); // images

    xmlstream->writeEndElement(); // session
}

Trace* Session::palate()
{
    return &palateTrace;
}

QList<Image*>* Session::palateImages()
{
    return &aPalateImages;
}

QList<int>* Session::palateTransparencies()
{
    return &aPalateTransparencies;
}

/*
int Session::palateUsesTrace()
{
    return nPalateInTrace;
}

void Session::setPalateUsesTrace(int trace)
{
    nPalateInTrace = trace;
}
*/

void Session::addToPalateTrace(QPoint pt)
{
    *(palateTrace.points()) << new QPoint(pt);
}

void Session::clearPalateTrace()
{
    palateTrace.points()->clear();
}

PalatronSettings* Session::palatronSettingsToUse()
{
    if( nPalatronSettingsFromSession >= 0 && nPalatronSettingsFromSession < subject->sessions()->count() )
    {
	return &(subject->sessions()->at(nPalatronSettingsFromSession)->palatronSettings);
    }
    else
    {
	return &palatronSettings;
    }
}
