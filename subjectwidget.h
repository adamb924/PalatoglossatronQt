#ifndef SUBJECTWIDGET_H
#define SUBJECTWIDGET_H

#include <QWidget>
#include <QList>

class Experiment;
class QTreeWidget;
class TreeItem;
class QPushButton;
class QStringList;

class SubjectWidget : public QWidget
{
Q_OBJECT
public:
    SubjectWidget(QWidget *parent = 0, Experiment *exp=0);
    QSize sizeHint() const;
    void drawTree();

private:
    QTreeWidget *tree;
    Experiment *experiment;

    QPushButton *bAddSubject, *bRemoveSubject;
    QPushButton *bAddSession, *bRemoveSession;

    int nSubject, nSession;
    void editSession();
    void editSubject();

    QList<TreeItem*> sessionitems;
    QStringList whoswho;

signals:
    void sessionClicked(int subject, int session);
    void subjectClicked(int subject);

public slots:
    void activateItem();
private slots:
    void changeOfImage(int subject, int session, int image);
    void selectedSession(int subject, int session);
    void selectedSubject(int subject);
    void addSubject();
    void removeSubject();
    void addSession();
    void removeSession();
    void doubleClickItem();
};

#endif // SUBJECTWIDGET_H
