#ifndef SUBJECT_H
#define SUBJECT_H

#include <QList>
#include <QString>
#include <QStringList>

class Session;
class Experiment;
class QXmlStreamWriter;

class Subject
{
public:
    Subject();
    ~Subject();
    Subject(QString name, Experiment *exp);

    QString name();
    void setName(QString n);
    QList<Session*>* sessions();
    QStringList* subjectData();
    void setSubjectData(int index, QString data);
    void setSubjectDataSize(int size);

    void serialize(QXmlStreamWriter *xmlstream);

    Experiment *experiment;

private:
    QString sName;
    QStringList aSubjectData;
    QList<Session*> aSessions;
};

#endif
