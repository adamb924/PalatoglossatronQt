#ifndef TRACKINGINTERFACE_H
#define TRACKINGINTERFACE_H

#include <QtPlugin>
#include <QPoint>
#include <QList>

QT_BEGIN_NAMESPACE
class QString;
class QImage;
QT_END_NAMESPACE


class TrackingInterface
{
public:
    virtual ~TrackingInterface() {}

    virtual QString name() const = 0;
    virtual void configure() const = 0;
    virtual QList<QPoint*> trace(QImage *img) = 0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(TrackingInterface,
		    "palatoglossatron.qt.trackinginterface/1.0")
QT_END_NAMESPACE


#endif // TRACKINGINTERFACE_H
