#ifndef ANNOTATIONWIDGET_H
#define ANNOTATIONWIDGET_H

#include <QWidget>
#include <QList>
#include <QTreeWidgetItem>

class Experiment;
class QTreeWidget;
class TreeItem;

class AnnotationWidget : public QWidget
{
Q_OBJECT
public:
    AnnotationWidget(QWidget *parent = 0, Experiment *exp=0, int subject=-1, int session=-1);
    ~AnnotationWidget() {}
    void drawTree();
    void setActive(bool act);

    QString video, ultrasound;
    QString free, grid;

private:
    bool active;
    QTabWidget *tabWidget;
    QTreeWidget *tree;
    QList<QTreeWidgetItem*> traceWidgets;
    QList<QTreeWidgetItem*> pointWidgets;
    Experiment *experiment;

signals:
    void traceClicked(int trace);
    void pointClicked(int point);
    void defineGrid();
    void updateGridLines(int lines);
    void sendGridToTracers();

public slots:
    void activateItem();
    void selectTrace(int tr);
    void selectPoint(int pt);
    void syncSignals();
private slots:
    void doubleClick( QTreeWidgetItem * item, int column );
};

#endif // ANNOTATIONWIDGET_H
