#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QList>
#include <QPoint>
#include <QImage>
#include <QColor>

class Trace;
class Session;
class Point;
class QXmlStreamWriter;

class Image
{
public:
    enum Interlacing {
	NoInterlacing,
	EvenRows,
	OddRows
    };

    Image();
    ~Image();
    Image(QString fn, int ntraces, int npoints, Session *parent);
    Image(QString fn, Session *parent);
    QString filename();
    QList<Trace*>* traces();
    QList<Point*>* points();
    void setPoint(int index, QPoint pos);
    void addToTrace(int index, QPoint pos);
    void setTracePoint(int trace, int index,QPoint pos);
    int pointNearest(int index, QPoint pos);
    void deleteFromEdge(int index, int pointindex);
    void removeTrace(int index);
    void removePoint(int index);

    static void deinterlace(QImage *img, Interlacing inter, int offset);

    QImage* image();
    QImage* dotView();
    QImage* createDotView(QRect region);

    int xoffset();
    int yoffset();
    double angle();

    bool palatron();

    QPoint* ul();
    QPoint* ur();
    QPoint* ll();
    QPoint* lr();

    bool mul();
    bool mur();
    bool mll();
    bool mlr();

    Image::Interlacing interlacing();
    void setInterlacing(Interlacing i);

    void setMul(bool value);
    void setMur(bool value);
    void setMll(bool value);
    void setMlr(bool value);

    void trackDots();

    void serialize(QXmlStreamWriter *xmlstream);

    bool isPalate();
    void setPalate(bool value);

    QPoint upperLeftToOverlay();

    Session* settingsSession();
    Session* palateSession();

private:
    QPoint findDotIn(QRect rect);

    void updateSettingsSession();
    void updatePalateSession();

    Session *session;
    Session *sessionForSettings;
    Session *sessionForPalate;

    Interlacing inter;

    bool bMUL, bMUR, bMLL, bMLR;

    bool bPalateImage;

    int nXoffset, nYoffset;
    double dAngle;

    QImage *img;

    QString sFilename;
    int nearnessThreshold;

    QList<Trace*> aTraces;
    QList<Point*> aPoints;

    QPoint pUL, pUR, pLL, pLR;
};

#endif
