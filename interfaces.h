#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QList>

QT_BEGIN_NAMESPACE
class QPainter;
class QWidget;
class QPainterPath;
class QPoint;
class QRect;
class QString;
class QStringList;
class QXmlStreamWriter;
class QImage;
class QPoint;
class Image;
class QPaintEvent;
class QLine;
QT_END_NAMESPACE

class AbstractPlugin
{
public:
    virtual void settings() = 0;
    virtual QString name() const = 0;
};

class TrackingInterface : public AbstractPlugin
{
public:
    virtual ~TrackingInterface() {}

    virtual QString name() const = 0;
    virtual bool initialized() = 0;
    virtual bool needsGrid() = 0;
    virtual void setGrid(QList<QLine>* grid) = 0;
    virtual QList<QPoint*> trace(QImage *img) = 0;
    virtual QString settingsToXML() = 0;
    virtual void receiveXMLSettings(QString xml) = 0;
    virtual void settings() = 0;

    virtual QStringList settingsTraceNames() const = 0;
    virtual bool setSettingTrace(int i, QList<QPoint*>* trace) = 0;
};

class DisplayInterface : public AbstractPlugin
{
public:
    virtual ~DisplayInterface() {}

    virtual QString name() const = 0;
    virtual void paint(QPainter* painter) = 0;
    virtual void calculate(Image *img) = 0;
    virtual void settings() = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(TrackingInterface,"palatoglossatron.qt.trackinginterface/1.0")
Q_DECLARE_INTERFACE(DisplayInterface,"palatoglossatron.qt.displayinterface/1.0")
QT_END_NAMESPACE

#endif
