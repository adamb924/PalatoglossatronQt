#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QRect>
#include <QColor>

#include "trace.h"
#include "point.h"
#include "palatronsettings.h"

class Image;
class Subject;
class QXmlStreamWriter;

class Session
{
public:
    Session();
    ~Session();
    Session(QString name, Subject *subj);
    QString name();
    QList<Image*>* images();

    void setName(QString n);
    void setSessionData(int index, QString data);
    void setSessionDataSize(int size);
    QStringList* sessionData();

    int palateFromSession();
    void setPalateFromSession(int index);

    int palatronSettingsFromSession();
    void setPalatronSettingsFromSession(int index);

    void addToPalateTrace(QPoint pt);
    void clearPalateTrace();

//    int palateUsesTrace();
//    void setPalateUsesTrace(int trace);

    Trace* palate();
    QList<Image*>* palateImages();
    QList<int>* palateTransparencies();

    QRect* ul();
    QRect* ur();
    QRect* ll();
    QRect* lr();

    QColor dotColor();
    void setDotColor(QColor col);
    int tolerance();
    void setTolerance(int tol);

    Subject *subject;

    PalatronSettings* palatronSettingsToUse();

    PalatronSettings palatronSettings;

    void serialize(QXmlStreamWriter *xmlstream);

private:
    QColor cDotColor;
    int nTolerance;

    Trace palateTrace;
    QList<Image*> aPalateImages;
    QList<int> aPalateTransparencies;

    QString sName;
    QStringList aSessionData;
    QList<Image*> aImages;

    int nPalateFromSession;
    int nPalatronSettingsFromSession;

    QRect rUL, rUR, rLL, rLR;
};

#endif
