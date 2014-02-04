#include "trace.h"

#include <QXmlStreamWriter>
#include <QPoint>
#include <QtDebug>

Trace::~Trace()
{
    qDeleteAll(aPoints.begin(), aPoints.end());
    qDeleteAll(aPointsTransformed.begin(), aPointsTransformed.end());
}

QList<QPoint*>* Trace::points()
{
    return &aPoints;
}

QList<QPoint*>* Trace::pointsTransformed()
{
    return &aPointsTransformed;
}

void Trace::serialize(QXmlStreamWriter *xmlstream)
{
    int i;

    xmlstream->writeStartElement("trace");

    xmlstream->writeStartElement("untransformed");
    for(i=0; i<aPoints.length(); i++)
    {
	xmlstream->writeEmptyElement("point");
	xmlstream->writeAttribute("x", QString::number( aPoints.at(i)->x() ));
	xmlstream->writeAttribute("y", QString::number( aPoints.at(i)->y() ));
    }
    xmlstream->writeEndElement(); // untransformed

    xmlstream->writeStartElement("transformed");
    for(i=0; i<aPointsTransformed.length(); i++)
    {
	xmlstream->writeEmptyElement("point");
	xmlstream->writeAttribute("x", QString::number( aPointsTransformed.at(i)->x() ));
	xmlstream->writeAttribute("y", QString::number( aPointsTransformed.at(i)->y() ));
    }
    xmlstream->writeEndElement(); // transformed

    xmlstream->writeEndElement(); // trace
}

void Trace::removePoint(QPoint pt)
{
    for(int i=0; i<aPoints.count(); i++)
	if( *(aPoints.at(i)) == pt )
	    delete aPoints.takeAt(i);
}

void Trace::nullifyPoint(int index)
{
    if( aPoints.count() > index )
	    aPoints[index] = new QPoint(-1,-1);
}
