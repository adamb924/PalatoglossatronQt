#include "image.h"
#include "trace.h"
#include "point.h"
#include "session.h"
#include "subject.h"
#include "experiment.h"
#include "defaultsettings.h"

#include <QList>
#include <QtDebug>
#include <math.h>
#include <QXmlStreamWriter>
#include <QPoint>

#include <QTime>

Image::Image()
{
}

Image::~Image()
{
    if(img != 0 ) { delete img; }
    qDeleteAll(aTraces.begin(), aTraces.end());
    qDeleteAll(aPoints.begin(), aPoints.end());
}

Image::Image(QString fn, int ntraces, int npoints, Session *parent)
{
    session = parent;

    sFilename = fn;

    nearnessThreshold = 3;

    pUL = QPoint(-1,-1);
    pUR = QPoint(-1,-1);
    pLL = QPoint(-1,-1);
    pLR = QPoint(-1,-1);

    bMUL = false; bMUR = false; bMLL = false; bMLR = false;

    bPalateImage = false;

    inter = Image::NoInterlacing;

    img = 0;

    nXoffset = 0;
    nYoffset = 0;
    dAngle = 0.0;

    int i;
    for(i=0; i<npoints; i++)
    {
	aPoints << new Point(-1,-1);
    }
    for(i=0; i<ntraces; i++)
    {
	aTraces << new Trace;
    }
}

Image::Image(QString fn, Session *parent)
{
    session = parent;

    sFilename = fn;

    nearnessThreshold = 3;

    pUL = QPoint(-1,-1);
    pUR = QPoint(-1,-1);
    pLL = QPoint(-1,-1);
    pLR = QPoint(-1,-1);

    bMUL = false; bMUR = false; bMLL = false; bMLR = false;

    bPalateImage = false;

    img = 0;
}

QString Image::filename()
{
    return sFilename;
}

QList<Trace*>* Image::traces()
{
    return &aTraces;
}

QList<Point*>* Image::points()
{
    return &aPoints;
}

void Image::setPoint(int index, QPoint pos)
{
    if(aPoints.length()==0 || index > aPoints.length())
    {
	return;
    }

    aPoints[index] = new Point(pos);

}

void Image::addToTrace(int index, QPoint pos)
{
    if(aTraces.length()==0 || index > aTraces.length())
    {
	return;
    }

    *(aTraces[index]->points()) << new QPoint(pos);
}

int Image::pointNearest(int index, QPoint pos)
{
    if(aTraces.length()==0 || index > aTraces.length())
    {
	return -1;
    }

    int nearest=-1, i;
    float distance, smallest=9999999999.0f;

    for(i = 0; i<aTraces[index]->points()->length(); i++)
    {
	distance =  sqrt( ( pos.x() - aTraces[index]->points()->at(i)->x() )*( pos.x() - aTraces[index]->points()->at(i)->x() ) + ( pos.y() - aTraces[index]->points()->at(i)->y() )*( pos.y() - aTraces[index]->points()->at(i)->y() ) );
	if(distance < smallest)
	{
	    nearest = i;
	    smallest = distance;
	}
    }
    return nearest;
}

void Image::deleteFromEdge(int index, int pointindex)
{
    if(aTraces.length()==0 || index > aTraces.length())
    {
	return;
    }
    if(pointindex == -1)
    {
	return;
    }
    int i;
    
    if( pointindex > aTraces[index]->points()->length()/2 ) // delete the second half
    {
//	qDebug() << "second half" << pointindex;
	for(i=aTraces[index]->points()->length()-1; i>pointindex; i--)
	{
	    aTraces[index]->points()->at(i)->setX(-1);
	    aTraces[index]->points()->at(i)->setY(-1);
	}
    }
    else // delete the first half
    {
	for(i=0; i<pointindex; i++)
	{
	    aTraces[index]->points()->at(i)->setX(-1);
	    aTraces[index]->points()->at(i)->setY(-1);
	}
    }

}

void Image::removeTrace(int index)
{
    if(aTraces.length()==0 || index > aTraces.length())
    {
	return;
    }
    aTraces[index]->points()->clear();
}

void Image::removePoint(int index)
{
    if(aPoints.length()==0 || index > aPoints.length())
    {
	return;
    }
    aPoints[index] = new Point(-1,-1);
}

QPoint* Image::ul()
{
    return &pUL;
}

QPoint* Image::ur()
{
    return &pUR;
}

QPoint* Image::ll()
{
    return &pLL;
}

QPoint* Image::lr()
{
    return &pLR;
}

QImage* Image::dotView()
{
    return createDotView(QRect(-1,-1,-1,-1));
}

QImage* Image::createDotView(QRect region)
{
    QImage *img;
    QImage clipped;
    if(region == QRect(-1,-1,-1,-1)) // requesting the whole image
    {
	clipped = QImage(sFilename);
    }
    else
    {
	img = new QImage(sFilename);
	clipped = img->copy(region);
	delete img;
    }

    if( region.top() != -1 && (region.top() % 2)==0) // even number of rows
    {
	deinterlace(&clipped, inter, 0);
    }
    else // odd
    {
	deinterlace(&clipped, inter, 1);
    }

    clipped.convertToFormat(QImage::Format_RGB32);
    QRgb *colorBits, *monoBits;
    QRgb tmp;
    int d;

    img = new QImage(clipped.width(),clipped.height(),QImage::Format_RGB32);

    monoBits = (QRgb*)img->bits();
    colorBits = (QRgb*)clipped.bits();

    int i;
    for(i=0; i< clipped.byteCount()/4; i++)
    {
	tmp = *(colorBits+i);
	d = (int)sqrt(  (qRed(sessionForSettings->dotColor().rgb()) - qRed(tmp))*(qRed(sessionForSettings->dotColor().rgb()) - qRed(tmp)) + (qGreen(sessionForSettings->dotColor().rgb()) - qGreen(tmp))*(qGreen(sessionForSettings->dotColor().rgb()) - qGreen(tmp)) + (qBlue(sessionForSettings->dotColor().rgb()) - qBlue(tmp))*(qBlue(sessionForSettings->dotColor().rgb()) - qBlue(tmp)) );
	if( d < sessionForSettings->tolerance() )
	    *(monoBits+i) = qRgba(255,255,255,255);
	else
	    *(monoBits+i) = qRgba(0,0,0,0);
    }

    return img;
}

QImage* Image::image()
{
    return new QImage(sFilename);
}

bool Image::mul()
{
    return bMUL;
}

bool Image::mur()
{
    return bMUR;
}

bool Image::mll()
{
    return bMLL;
}

bool Image::mlr()
{
    return bMLR;
}

void Image::setMul(bool value)
{
    bMUL = value;
}

void Image::setMur(bool value)
{
    bMUR = value;
}

void Image::setMll(bool value)
{
    bMLL = value;
}

void Image::setMlr(bool value)
{
    bMLR = value;
}

Session* Image::settingsSession()
{
    updateSettingsSession();
    return sessionForSettings;
}

Session* Image::palateSession()
{
    updatePalateSession();
    return sessionForPalate;
}

void Image::updateSettingsSession()
{
    if( session->palatronSettingsFromSession() < 0 || session->palatronSettingsFromSession() >= session->subject->sessions()->length() )
    {
	sessionForSettings = session;
    }
    else
    {
	sessionForSettings = session->subject->sessions()->at(session->palatronSettingsFromSession());
    }
}

void Image::updatePalateSession()
{
    if( session->palateFromSession() < 0 || session->palateFromSession() >= session->subject->sessions()->length() )
    {
	sessionForPalate = session;
    }
    else
    {
	sessionForPalate = session->subject->sessions()->at(session->palateFromSession());
    }
}


void Image::trackDots()
{
    updateSettingsSession();

    if( !bMUL && sessionForSettings->ul()->topLeft() != QPoint(-1,-1) )
    {
	pUL = findDotIn(*(sessionForSettings->ul()));
    }
    if( !bMUR && sessionForSettings->ur()->topLeft() != QPoint(-1,-1) )
    {
	pUR = findDotIn(*(sessionForSettings->ur()));
    }
    if( !bMLL && sessionForSettings->ll()->topLeft() != QPoint(-1,-1) )
    {
	pLL = findDotIn(*(sessionForSettings->ll()));
    }
    if( !bMLR && sessionForSettings->lr()->topLeft() != QPoint(-1,-1) )
    {
	pLR = findDotIn(*(sessionForSettings->lr()));
    }
}

QPoint Image::findDotIn(QRect rect)
{
    QImage *img = createDotView(rect);

    QRgb *line;
    int i,j;
    int count=0, xsum=0, ysum=0;
    for(i=0; i<img->height(); i++)
    {
	line = (QRgb*)img->scanLine(i);
	for(j=0; j<img->width(); j++)
	{
	    if( *(line+j) > 0)
	    {
		count++;
		ysum += i;
		xsum += j;
	    }
	}
    }
    delete img;

    if(xsum==0 || ysum==0)
    {
	return QPoint(-1,-1);
    }
    else
    {
	return (QPoint(xsum/count,ysum/count) + rect.topLeft() );
    }
}

bool Image::palatron()
{
//    qDebug() << "Image::palatron begin";

    updateSettingsSession();

    int i, j;

    if( pUL == QPoint(-1,-1) || pUR == QPoint(-1,-1) || pLL == QPoint(-1,-1) || pLR == QPoint(-1,-1) )
    {
	for(i = 0; i < aTraces.length(); i++)
	{
	    aTraces.at(i)->pointsTransformed()->clear();
	}
	return false;
    }

    QImage img(sFilename);

//    qDebug() << "Palatron running";

/*
    aTraces << new Trace;
    aTraces.last()->aPoints << new QPoint(283,300);
    aTraces.last()->aPoints << new QPoint(287,293);
    aTraces.last()->aPoints << new QPoint(292,281);
    aTraces.last()->aPoints << new QPoint(294,277);
    aTraces.last()->aPoints << new QPoint(296,274);
    aTraces.last()->aPoints << new QPoint(298,269);
    aTraces.last()->aPoints << new QPoint(299,267);
    aTraces.last()->aPoints << new QPoint(301,264);
    aTraces.last()->aPoints << new QPoint(303,259);
    aTraces.last()->aPoints << new QPoint(307,253);
    aTraces.last()->aPoints << new QPoint(310,248);
*/
    short OverlayX, OverlayY;
    double Angle, UsScale,tranlrmm,ortranrmm,ortranlmm;
    double orheaddist, orheadangle, vidoriginx, vidoriginy, vidscale, tranangle, ortrandist, ortranangle, headangle, htangle, headx, heady, centerheaddist, centerheadangle, rotatedheadx, rotatedheady;
    double imagecenterx, imagecentery, usoriginx, usoriginy;
    double vertical_distortion_correction, horizontal_distortion_correction;
    short ulx,uly,urx,ury,llx,lly,lrx,lry;
    short XOffset, YOffset;
    double AngleOffset;
    double X, Y, tmpX, tmpY;

    OverlayX = sessionForSettings->palatronSettings.OverlayX;
    OverlayY = sessionForSettings->palatronSettings.OverlayY;
    Angle = sessionForSettings->palatronSettings.Angle;
    UsScale = sessionForSettings->palatronSettings.UsScale;
    tranlrmm = sessionForSettings->palatronSettings.tranlrmm;
    ortranrmm = sessionForSettings->palatronSettings.ortranrmm;
    ortranlmm = sessionForSettings->palatronSettings.ortranlmm;
    usoriginx = sessionForSettings->palatronSettings.usoriginx;
    usoriginy = sessionForSettings->palatronSettings.usoriginy;
    vertical_distortion_correction = sessionForSettings->palatronSettings.vertical_distortion_correction;
    horizontal_distortion_correction = sessionForSettings->palatronSettings.horizontal_distortion_correction;

    qDebug() << "Image::palatron()" << OverlayX << OverlayY;

/*
    OverlayX = sessionForSettings->subject->experiment->ds->OverlayX;
    OverlayY = sessionForSettings->subject->experiment->ds->OverlayY;
    Angle = sessionForSettings->subject->experiment->ds->Angle;
    UsScale = sessionForSettings->subject->experiment->ds->UsScale;
    tranlrmm = sessionForSettings->subject->experiment->ds->tranlrmm;
    ortranrmm = sessionForSettings->subject->experiment->ds->ortranrmm;
    ortranlmm = sessionForSettings->subject->experiment->ds->ortranlmm;
    usoriginx = sessionForSettings->subject->experiment->ds->usoriginx;
    usoriginy = sessionForSettings->subject->experiment->ds->usoriginy;
    vertical_distortion_correction = sessionForSettings->subject->experiment->ds->vertical_distortion_correction;
    horizontal_distortion_correction = sessionForSettings->subject->experiment->ds->horizontal_distortion_correction;
*/

    imagecenterx = (sessionForSettings->palatronSettings.horizontal_distortion_correction*img.width())/2;
    imagecentery = (sessionForSettings->palatronSettings.vertical_distortion_correction*img.height())/2;

//    qDebug() << OverlayX << Angle << UsScale << tranlrmm << ortranrmm << ortranlmm <<  imagecenterx << imagecentery  << usoriginx  << usoriginy;
//    qDebug() << vertical_distortion_correction << horizontal_distortion_correction;


    ulx = pUL.x() * horizontal_distortion_correction;
    uly = -1* pUL.y() * vertical_distortion_correction;
    urx = pUR.x() * horizontal_distortion_correction;
    ury = -1* pUR.y() * vertical_distortion_correction;
    llx = pLL.x() * horizontal_distortion_correction;
    lly = -1* pLL.y() * vertical_distortion_correction;
    lrx = pLR.x() * horizontal_distortion_correction;
    lry = -1* pLR.y() * vertical_distortion_correction;
/*
    ulx = pUL.x() * horizontal_distortion_correction;
    uly = pUL.y() * vertical_distortion_correction;
    urx = pUR.x() * horizontal_distortion_correction;
    ury = pUR.y() * vertical_distortion_correction;
    llx = pLL.x() * horizontal_distortion_correction;
    lly = pLL.y() * vertical_distortion_correction;
    lrx = pLR.x() * horizontal_distortion_correction;
    lry = pLR.y() * vertical_distortion_correction;
*/

    /*
    ulx = 74;
    uly = 89* vertical_distortion_correction;
    urx = 634;
    ury = 108* vertical_distortion_correction;
    llx = 144;
    lly = 398* vertical_distortion_correction;
    lrx = 619;
    lry = 435* vertical_distortion_correction;
*/

    vidscale = tranlrmm/sqrt(  (lrx-llx)*(lrx-llx) + (lly-lry)*(lly-lry));
    ortrandist = ortranlmm / vidscale;
    ortranangle = atan(-1.0f*ortranrmm*sin(acos( (tranlrmm*tranlrmm + ortranrmm*ortranrmm - ortranlmm*ortranlmm) / (2.0f * tranlrmm * ortranrmm))) / (tranlrmm - ortranrmm * cos(acos(( tranlrmm*tranlrmm + ortranrmm*ortranrmm - ortranlmm*ortranlmm) / (2 * tranlrmm * ortranrmm)))));

    tranangle = atan((double)(lly - lry)/(double)(lrx - llx));

//    qDebug() << "tranangle" << (lly - lry) << (lrx - llx) << (double)(lly - lry)/(double)(lrx - llx) << atan((double)(lly - lry)/(double)(lrx - llx));

    headangle = atan((double)(uly - ury)/(double)(urx - ulx));
    htangle = headangle - tranangle;

    AngleOffset = Angle*(-3.1415926535897932384626433832795/180.0f) - htangle;
//    AngleOffset = htangle - Angle*(-3.1415926535897932384626433832795/180.0f);

//    qDebug() << "angles" << headangle << htangle << AngleOffset;

    vidoriginx = llx - (ortrandist * cos(ortranangle - tranangle));
    vidoriginy = lly - (ortrandist * sin(ortranangle - tranangle));

    orheaddist = vidscale/UsScale * sqrt((ulx - vidoriginx)*(ulx - vidoriginx) + (uly - vidoriginy)*(uly - vidoriginy));
    orheadangle = acos((ulx - vidoriginx)/(sqrt( (ulx - vidoriginx)*(ulx - vidoriginx) + (vidoriginy - uly)*(vidoriginy - uly) ))) - tranangle;

    headx = usoriginx + orheaddist * cos(orheadangle);
    heady = usoriginy - orheaddist * sin(orheadangle);

    centerheaddist = sqrt( (headx - imagecenterx)*(headx - imagecenterx) + (imagecentery - heady)*(imagecentery - heady));
    centerheadangle = atan((headx - imagecenterx)/(imagecentery - heady));

    rotatedheadx = imagecenterx + (centerheaddist * sin(centerheadangle + AngleOffset));
    rotatedheady = imagecentery - (centerheaddist * cos(centerheadangle + AngleOffset));

    XOffset = (short)(OverlayX - rotatedheadx);
    YOffset = (short)(OverlayY - rotatedheady);

//    qDebug() << "setting XOffset" << XOffset;
/*
//    qDebug() << vidoriginx;
//    qDebug() << vidoriginy;
    qDebug() << rotatedheadx; // close
    qDebug() << rotatedheady; // close
//    qDebug() << vidscale;
//    qDebug() << ortrandist;
//    qDebug() << ortranangle;
//    qDebug() << tranangle;
    qDebug() << AngleOffset;
    qDebug() << XOffset;
    qDebug() << YOffset;
*/
    // negative because Jeff's code outputs a clockwise rotation
    AngleOffset *= -1;

//    qDebug() << "here";

//    qDebug() << "imagecentery" << imagecentery;

    for(i = 0; i < aTraces.length(); i++)
    {
	aTraces.at(i)->pointsTransformed()->clear();
	for( j = 0; j < aTraces.at(i)->points()->length(); j++ )
	{
	    if( aTraces.at(i)->points()->at(j)->x() == -1 && aTraces.at(i)->points()->at(j)->y() == -1 ) { continue; }

	    X = aTraces.at(i)->points()->at(j)->x() * horizontal_distortion_correction;
	    // flip the vertical coordinate
	    Y = -1 * aTraces.at(i)->points()->at(j)->y() * vertical_distortion_correction;

	    if(i==1 && j==0) { qDebug() << "Palatron X" << X; }

	    if( sessionForSettings->subject->experiment->getTraceLocation(i) == Experiment::Ultrasound )
	    {
		// rotate first

		// bring it back to the origin
		X -= imagecenterx;
		Y -= imagecentery;

//		if(i==1 && j==0) { qDebug() << "Palatron X" << X; }

		// rotate it about the origin
		tmpX = X*cos(AngleOffset) - Y*sin(AngleOffset);
		tmpY = Y*cos(AngleOffset) + X*sin(AngleOffset);

//		if(i==1 && j==0) { qDebug() << "Palatron tmpx" << tmpX; }

		// send it back to image-centered space
		X = tmpX + imagecenterx;
		Y = tmpY + imagecentery;

//		if(i==1 && j==0) { qDebug() << "Palatron X" << X; }

//		qDebug() << "after rotation, before translation" << X << Y;

		// do the translation as well
		X += XOffset;
		Y += YOffset;

//		if(i==1 && j==0) { qDebug() << "Palatron X" << X; }
	    }
	    // flip the vertical coordinate back
	    Y *= -1;

	    *(aTraces.at(i)->pointsTransformed()) << new QPoint(X,Y);
	}
    }

    // store the numbers locally
    dAngle = AngleOffset;
    nXoffset = XOffset;
    nYoffset = YOffset;

    // now for the measurement points
    for(i = 0; i < aPoints.length(); i++)
    {
	if( aPoints.at(i)->x() == -1 && aPoints.at(i)->y() == -1 ) { continue; }

	X = aPoints.at(i)->x() * horizontal_distortion_correction;
	// flip the vertical coordinate
	Y = -1 * aPoints.at(i)->y() * vertical_distortion_correction;

	if( sessionForSettings->subject->experiment->getPointLocation(i) == Experiment::Ultrasound )
	{
	    // rotate first

	    // bring it back to the origin
	    X -= imagecenterx;
	    Y -= imagecentery;

	    // rotate it about the origin
	    tmpX = X*cos(AngleOffset) - Y*sin(AngleOffset);
	    tmpY = Y*cos(AngleOffset) + X*sin(AngleOffset);

	    // send it back to image-centered space
	    X = tmpX + imagecenterx;
	    Y = tmpY + imagecentery;

	    // do the translation as well
	    X += XOffset;
	    Y += YOffset;
	}
	// flip the vertical coordinate back
	Y *= -1;

	aPoints[i]->setPointTransformed(X,Y);
    }
/*
    if(aTraces.count()>1)
    {
	qDebug() << "trace";
	for(i=0; i<aTraces.at(1)->pointsTransformed()->count(); i++)
	{
	    qDebug() << *(aTraces.at(1)->pointsTransformed()->at(i));
	}
    }
*/
//    qDebug() << aTracesPalatroned.length() << "traces and" <<  aPointsPalatroned.length() << "points";
//    qDebug() << "Image::palatron end";

    return true;
}

QPoint Image::upperLeftToOverlay()
{
    double vertical_distortion_correction = sessionForSettings->palatronSettings.vertical_distortion_correction;
    double horizontal_distortion_correction = sessionForSettings->palatronSettings.horizontal_distortion_correction;
    double ulx = pUL.x() * horizontal_distortion_correction;
    double uly = -1* pUL.y() * vertical_distortion_correction;
    double OverlayX = sessionForSettings->palatronSettings.OverlayX;
    double OverlayY = sessionForSettings->palatronSettings.OverlayY;
    return QPoint(OverlayX - ulx,OverlayY - uly);
}

void Image::serialize(QXmlStreamWriter *xmlstream)
{
    int i;

    // make sure everything is current
    palatron();

    xmlstream->writeStartElement("image");

    xmlstream->writeTextElement("filename",sFilename);

    switch(inter)
    {
    case Image::EvenRows:
	xmlstream->writeTextElement("interlacing","even");
	break;
    case Image::OddRows:
	xmlstream->writeTextElement("interlacing","odd");
	break;
    default:
	xmlstream->writeTextElement("interlacing","none");
	break;
    }

    xmlstream->writeStartElement("dots");

    xmlstream->writeEmptyElement("upperLeft");
    xmlstream->writeAttribute("x",QString::number(pUL.x()));
    xmlstream->writeAttribute("y",QString::number(pUL.y()));
    xmlstream->writeAttribute("manuallySpecified",QString::number(bMUL));

    xmlstream->writeEmptyElement("upperRight");
    xmlstream->writeAttribute("x",QString::number(pUR.x()));
    xmlstream->writeAttribute("y",QString::number(pUR.y()));
    xmlstream->writeAttribute("manuallySpecified",QString::number(bMUR));

    xmlstream->writeEmptyElement("lowerLeft");
    xmlstream->writeAttribute("x",QString::number(pLL.x()));
    xmlstream->writeAttribute("y",QString::number(pLL.y()));
    xmlstream->writeAttribute("manuallySpecified",QString::number(bMLL));

    xmlstream->writeEmptyElement("lowerRight");
    xmlstream->writeAttribute("x",QString::number(pLR.x()));
    xmlstream->writeAttribute("y",QString::number(pLR.y()));
    xmlstream->writeAttribute("manuallySpecified",QString::number(bMLR));

    xmlstream->writeEndElement(); // dots

/*
-    bool bMUL, bMUR, bMLL, bMLR;

    QString sFilename;
    int nearnessThreshold; // not stored

-    QList<Trace*> aTraces;
-    QList<Point*> aPoints;

-    QPoint pUL, pUR, pLL, pLR;
-    bPalateImage
*/
//    xmlstream->writeTextElement("palateImage",QString::number(bPalateImage));

    xmlstream->writeStartElement("traces");
    for(i=0; i<aTraces.length(); i++)
    {
	aTraces.at(i)->serialize(xmlstream);
    }
    xmlstream->writeEndElement(); // traces

    xmlstream->writeStartElement("measurementPoints");
    for(i=0; i<aPoints.length(); i++)
    {
	aPoints.at(i)->serialize(xmlstream);
    }
    xmlstream->writeEndElement(); // measurementPoints

    xmlstream->writeEndElement(); // image
}

void Image::setTracePoint(int trace, int index, QPoint pos)
{
//    qDebug() << trace << index << pos;
    if(trace < 0 || trace >= aTraces.length() ) { return; }
    while(index >= aTraces.at(trace)->points()->length() )
    {
	*(aTraces.at(trace)->points()) << new QPoint(-1,-1);
    }
//    qDebug() << aTraces.at(trace)->points()->length();
    aTraces.at(trace)->points()->at(index)->setX(pos.x());
    aTraces.at(trace)->points()->at(index)->setY(pos.y());
//    qDebug() << index << aTraces.at(trace)->points()->length();
}

bool Image::isPalate()
{
    return bPalateImage;
}

void Image::setPalate(bool value)
{
    bPalateImage = value;
}

int Image::xoffset()
{
    return nXoffset;
}

int Image::yoffset()
{
    return nYoffset;
}

double Image::angle()
{
    return dAngle;
}

Image::Interlacing Image::interlacing()
{
    return inter;
}

void Image::setInterlacing(Interlacing i)
{
    inter = i;
}

void Image::deinterlace(QImage *img, Interlacing inter, int offset = 0)
{
    if(img == 0) { return; }
    // HACK!!!!!!
    offset = 0;

    int i, j;
    int start, end;
    QRgb above, below;
    switch(inter)
    {
    case Image::EvenRows:
	start = 1;
	if( img->height() % 2 == 0 ) // is even
	{
	    end = img->height() - 3 + offset;
	}
	else // is odd
	{
	    end = img->height() - 2 + offset;
	}
	break;
    case Image::OddRows:
	start = 2;
	if( img->height() % 2 == 0 ) // is even
	{
	    end = img->height() - 2 + offset;
	}
	else // is odd
	{
	    end = img->height() - 3 + offset;
	}
	break;
    default:
	return;
	break;
    }

    for(i=start; i<end; i+=2)
    {
	for(j=0; j < img->width(); j++)
	{
	    above = *( ((QRgb*)img->scanLine(i-1)) + j );
	    below = *( ((QRgb*)img->scanLine(i+1)) + j );
/*
	    int test1, test2;
	    test1 = ((qRed(above)+qRed(below))/2);
	    test2 = ((qRed(above)+qRed(below))/2)<<16;
	    qDebug() << test1 << test2;
	    return;
*/
	    *( ((QRgb*)img->scanLine(i)) + j ) = 0x00000000 + (((qRed(above)+qRed(below))/2)<<16)  + (((qGreen(above)+qGreen(below))/2)<<8) + ((qBlue(above)+qBlue(below))/2);
//	    *( ((QRgb*)img->scanLine(i)) + j ) = 0xffffffff; // white lines
//	    *( ((QRgb*)img->scanLine(i)) + j ) = 0x00ffffff; // white lines
	}
    }

//    (QRgb*)img->scanLine(i);
}
