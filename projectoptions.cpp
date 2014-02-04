#include "projectoptions.h"
#include "listeditorwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
#include <QtDebug>

Projectoptions::Projectoptions(QWidget *parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout;

    name = new QLineEdit;
    description = new QLineEdit;

    vlayout->addWidget(new QLabel(tr("Experiment Name")));
    vlayout->addWidget(name);
    vlayout->addWidget(new QLabel(tr("Description")));
    vlayout->addWidget(description);

    QStringList traceList;
    traceList << "Tongue Trace" << "Velum";
    traceWidget = new ListEditorWidget(traceList);
    vlayout->addWidget(new QLabel(tr("Interpretations of Traces")));
    vlayout->addWidget(traceWidget);


    QStringList pointList;
    pointList << "Upper Lip" << "Lower Lip" << "Tip of Nose";
    vlayout->addWidget(new QLabel(tr("Interpretations of Points")));
    pointWidget = new ListEditorWidget(pointList);
    vlayout->addWidget(pointWidget);


    QStringList subjectList;
    subjectList << "Code" << "Sex" << "Native Language" << "Other language experience" << "Note";
    vlayout->addWidget(new QLabel(tr("Data Fields for Subjects")));
    subjectWidget = new ListEditorWidget(subjectList);
    vlayout->addWidget(subjectWidget);

    QStringList sessionList;
    sessionList << "Date" << "Note";
    vlayout->addWidget(new QLabel(tr("Data Fields for Sessions")));
    sessionWidget = new ListEditorWidget(sessionList);
    vlayout->addWidget(sessionWidget);

    createExperiment = new QPushButton(tr("Create Experiment"));
    vlayout->addWidget(createExperiment);

    this->setLayout(vlayout);
}
