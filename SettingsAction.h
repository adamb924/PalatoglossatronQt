#ifndef SETTINGSACTION_H
#define SETTINGSACTION_H

#include <QAction>
#include "interfaces.h"
#include <QtDebug>
class QString;

class SettingsAction : public QAction
{
    Q_OBJECT
public:
    SettingsAction( const QString &text, AbstractPlugin *p, QObject *parent ) : QAction(text,parent)
    {
	plugin = p;
    }
    AbstractPlugin *plugin;

public slots:
    void mytrigger()
    {
	plugin->settings();
    }
};

class DoubleIndexAction : public QAction
{
    Q_OBJECT
public:
    DoubleIndexAction( const QString &text, int I, int J, QObject *parent ) : QAction(text,parent)
    {
	i = I;
	j = J;
    }

    int i, j;

signals:
    void activated(int i, int j);

public slots:
    void mytrigger()
    {
	emit activated(i,j);
    }
};

#endif // SETTINGSACTION_H
