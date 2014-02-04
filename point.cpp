#include "point.h"

#include <QString>
#include <QXmlStreamWriter>
#include <QPoint>
#include <QtDebug>

Point::Point()
{
    point = new QPoint(-1,-1);
    pointTransformed = new QPoint(-1,-1);
}

Point::Point(int x, int y)
{
    point = new QPoint(x,y);
    pointTransformed = new QPoint(-1,-1);
}

Point::Point(QPoint pt)
{
    point = new QPoint(pt);
    pointTransformed = new QPoint(-1,-1);
}

Point::~Point()
{
    delete point;
    delete pointTransformed;
}

QPoint* Point::pt()
{
    return point;
}

QPoint* Point::ptTransformed()
{
    return pointTransformed;
}

int Point::x()
{
    return point->x();
}

int Point::y()
{
    return point->y();
}

int Point::Tx()
{
//    qDebug() << pointTransformed;
    return pointTransformed->x();
}

int Point::Ty()
{
    return pointTransformed->y();
}

void Point::setPointTransformed(int x, int y)
{
    pointTransformed->setX(x);
    pointTransformed->setY(y);
}


void Point::serialize(QXmlStreamWriter *xmlstream)
{
    xmlstream->writeStartElement("measurementPoint");

    xmlstream->writeEmptyElement("untransformed");
    xmlstream->writeAttribute("x", QString::number(point->x()));
    xmlstream->writeAttribute("y", QString::number(point->y()));

    xmlstream->writeEmptyElement("transformed");
    xmlstream->writeAttribute("x", QString::number(pointTransformed->x()));
    xmlstream->writeAttribute("y", QString::number(pointTransformed->y()));

    xmlstream->writeEndElement(); // measurementPoint
}
