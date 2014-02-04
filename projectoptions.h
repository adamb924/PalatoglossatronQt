#ifndef PROJECTOPTIONS_H
#define PROJECTOPTIONS_H

#include <QWidget>
#include <QScrollArea>

class QLineEdit;
class QStringListModel;
class QPushButton;
class ListEditorWidget;

class Projectoptions : public QWidget
{
    Q_OBJECT

public:
    Projectoptions(QWidget *parent = 0);
    QLineEdit *name, *description;
    ListEditorWidget *traceWidget, *pointWidget, *subjectWidget, *sessionWidget;
    QPushButton *createExperiment;
};

#endif // PROJECTOPTIONS_H
