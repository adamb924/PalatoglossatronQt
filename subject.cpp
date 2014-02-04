#include "subject.h"
#include "session.h"
#include "experiment.h"

#include <QtDebug>
#include <QString>
#include <QXmlStreamWriter>

Subject::Subject()
{

}

Subject::~Subject()
{
    qDeleteAll(aSessions.begin(), aSessions.end());
}

Subject::Subject(QString name, Experiment *exp)
{
    experiment = exp;

    sName = name;
/*
    aSessions << new Session("Session 1",this);
    aSessions << new Session("Session 2",this);
    aSessions << new Session("Session 3",this);
*/
    for(int i=0; i<experiment->getSubjectDataInterpretations()->length(); i++)
    {
	aSubjectData << "";
    }
}

QString Subject::name()
{
    return sName;
}

QList<Session*>* Subject::sessions()
{
    return &aSessions;
}

QStringList* Subject::subjectData()
{
    return &aSubjectData;
}

void Subject::setName(QString n)
{
    sName = n;
}

void Subject::setSubjectData(int index, QString data)
{
    if(index > -1 && index < aSubjectData.length())
    {
	if(index >= aSubjectData.length())
	    setSubjectDataSize(index);
	aSubjectData[index] = data;
    }
}

void Subject::setSubjectDataSize(int size)
{
    while( aSubjectData.length() <= size )
    {
	aSubjectData << "";
    }
}

void Subject::serialize(QXmlStreamWriter *xmlstream)
{
/*
-    QString sName;
-    QStringList aSubjectData;
-    QList<Session*> aSessions;*/

    int i;

    xmlstream->writeStartElement("subject");
    xmlstream->writeTextElement("subjectName",sName);

    xmlstream->writeStartElement("subjectData");
    for(i=0; i<aSubjectData.length(); i++)
    {
	xmlstream->writeStartElement("datum");
	xmlstream->writeAttribute("id",QString::number(i));
	xmlstream->writeCharacters(aSubjectData.at(i));
	xmlstream->writeEndElement(); // datum
    }
    xmlstream->writeEndElement(); // subjectData

    for(i=0; i < aSessions.length(); i++)
    {
	aSessions.at(i)->serialize(xmlstream);
    }



    xmlstream->writeEndElement(); // subject
}
