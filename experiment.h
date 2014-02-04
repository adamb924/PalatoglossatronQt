#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <QString>
#include <QStringList>
#include <QList>

#include "globals.h"

class Subject;
class QStringList;
class DefaultSettings;
class QLine;
class QXmlStreamReader;

class Experiment
{
public:
    enum Location {
	Ultrasound,
	Video,
	Error
    };

    enum TraceType {
	Free,
	Grid,
	ErrorTraceType
    };


    Experiment();
    ~Experiment();

    DefaultSettings *ds;

    QString currentFilename;

    QList<Subject*> aSubjects;

    void setName(QString name);
    void setDescription(QString description);
    QString name();
    QString description();

    void setTraceInterpretations(QStringList newdata);
    QStringList* getTraceInterpretations();

    void setPointInterpretations(QStringList newdata);
    QStringList* getPointInterpretations();

    void setSubjectDataInterpretations(QStringList newdata);
    QStringList* getSubjectDataInterpretations();

    void setSessionDataInterpretations(QStringList newdata);
    QStringList* getSessionDataInterpretations();


    bool validSubject(int subject);
    bool validSession(int subject, int session);
    bool validImage(int subject, int session, int image);

    void addSubject(QString name);

    QList<Experiment::Location>* getPointLocations();
    QList<Experiment::Location>* getTraceLocations();
    void setPointLocation(int index, Experiment::Location loc);
    void setTraceLocation(int index, Experiment::Location loc);
    Experiment::Location getPointLocation(int index);
    Experiment::Location getTraceLocation(int index);

    QList<Experiment::TraceType>* getTraceTypes();
    void setTraceType(int index, Experiment::TraceType loc);
    Experiment::TraceType getTraceType(int index);

    bool readFromFile(QString fn);
    void serialize(QString fn);

    QLine* fanLeft();
    QLine* fanRight();
    int fanLines();
    void setFanLines(int l);
    QList<QLine>* grid();
    void updateGrid();

    QString tracer();
    void setTracer(QString name);

    void setPluginSettings(QString label, QString xml);
    bool hasPluginSettings(QString label);
    QString pluginSettings(QString label);

    void addSessionFromTabDelimitedFile(QString filename, QString sSubject, QString sSession);

private:
    QString sName, sDescription;
    QStringList aTraceInterpretations;
    QStringList aPointInterpretations;
    QStringList aSubjectDataInterpretations;
    QStringList aSessionDataInterpretations;

    QString tracerName;

    QStringList aPluginSettingsLabels;
    QStringList aPluginSettings;

    QList<Location> aTraceLocations;
    QList<Location> aPointLocations;

    QList<TraceType> aTraceTypes;

    QLine *lFanLeft, *lFanRight;
    int nFanLines;
    QList<QLine> aGrid;
};

#endif
