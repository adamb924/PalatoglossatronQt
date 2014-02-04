#ifndef TRACE_H
#define TRACE_H

class QString;
class QImage;
class QPoint;
class QXmlStreamWriter;

#include <QList>

class Trace
{
public:
    Trace() {}
    ~Trace();

    QList<QPoint*>* points();
    QList<QPoint*>* pointsTransformed();

    void removePoint(QPoint pt);
    void nullifyPoint(int index);

    void serialize(QXmlStreamWriter *xmlstream);

private:
    QList<QPoint*> aPoints;
    QList<QPoint*> aPointsTransformed;
};

#endif
