#include "subjectwidget.h"
#include "experiment.h"
#include "subject.h"
#include "session.h"
#include "treeitem.h"
#include "dataentrywidget.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QtDebug>
#include <QPushButton>
#include <QInputDialog>
#include <QDir>

SubjectWidget::SubjectWidget(QWidget *parent, Experiment *exp) :
    QWidget(parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *sessionLayout = new QHBoxLayout;
    QHBoxLayout *subjectLayout = new QHBoxLayout;
    tree = new QTreeWidget;
    tree->setHeaderHidden(true);
    experiment = exp;

    //   QPushButton bAddSubject, bRemoveSubject;
    //    QPushButton bAddSession, bRemoveSession;
    bAddSubject = new QPushButton(tr("Add Subject"));
    bRemoveSubject = new QPushButton(tr("Remove Subject"));
    subjectLayout->addWidget(bAddSubject);
    subjectLayout->addWidget(bRemoveSubject);

    bAddSession = new QPushButton(tr("Add Session"));
    bRemoveSession = new QPushButton(tr("Remove Session"));
    sessionLayout->addWidget(bAddSession);
    sessionLayout->addWidget(bRemoveSession);

    vlayout->addWidget(tree);
    vlayout->addLayout(subjectLayout);
    vlayout->addLayout(sessionLayout);

    this->setLayout(vlayout);

    connect(tree,SIGNAL(itemSelectionChanged()),this,SLOT(activateItem()));
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickItem()));
    connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(activateItem()));

    connect(this,SIGNAL(sessionClicked(int,int)),this,SLOT(selectedSession(int,int)));
    connect(this,SIGNAL(subjectClicked(int)),this,SLOT(selectedSubject(int)));

    connect(bAddSubject,SIGNAL(clicked()),this,SLOT(addSubject()));
    connect(bAddSession,SIGNAL(clicked()),this,SLOT(addSession()));
    connect(bRemoveSubject,SIGNAL(clicked()),this,SLOT(removeSubject()));
    connect(bRemoveSession,SIGNAL(clicked()),this,SLOT(removeSession()));

    // this did not work
//    disconnect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),tree,SLOT(expandItem(const QTreeWidgetItem*)));
    tree->setExpandsOnDoubleClick(false);

    drawTree();
}

void SubjectWidget::drawTree()
{
    int i, j;
    TreeItem *it, *subitem;

    qDeleteAll(sessionitems.begin(), sessionitems.end());
    sessionitems.clear();
    tree->clear();

    bAddSession->setEnabled(false);
    bRemoveSession->setEnabled(false);
    bRemoveSubject->setEnabled(false);

    for(i=0; i<experiment->aSubjects.length(); i++)
    {
	it = new TreeItem(tree,TreeItem::Subject,i);
	it->setText(0, experiment->aSubjects.at(i)->name());
	tree->addTopLevelItem(it);
	it = (TreeItem*)tree->topLevelItem(tree->topLevelItemCount()-1);
	it->setExpanded(true);
	for(j=0; j < experiment->aSubjects.at(i)->sessions()->length(); j++)
	{
	    subitem = new TreeItem(it,TreeItem::Session,i,j);
	    subitem->setText(0, experiment->aSubjects.at(i)->sessions()->at(j)->name());
	    sessionitems << subitem;
	    whoswho << QString::number(i) + "," + QString::number(j);
	    it->addChild(subitem);
	}
    }
}

void SubjectWidget::activateItem()
{
    TreeItem *curr;
    curr = (TreeItem*)tree->currentItem();
//    qDebug() << curr->subject << curr->session << curr->image << curr->trace << curr->point;

    switch(curr->type())
    {
    case TreeItem::Session:
	emit sessionClicked(curr->subject, curr->session);
	break;
    case TreeItem::Subject:
	emit subjectClicked(curr->subject);
	break;
    default:
	break;
    }
}

void SubjectWidget::doubleClickItem()
{
    TreeItem *curr;
    curr = (TreeItem*)tree->currentItem();

    switch(curr->type())
    {
    case TreeItem::Session:
	editSession();
	break;
    case TreeItem::Subject:
	editSubject();
	break;
    default:
	break;
    }
}

QSize SubjectWidget::sizeHint() const
{
    return QSize(150,300);
}

void SubjectWidget::selectedSession(int subject, int session)
{
//    qDebug() << "selectedSession";
    nSubject = subject;
    nSession = session;
    bAddSession->setEnabled(true);
    bRemoveSession->setEnabled(true);
    bRemoveSubject->setEnabled(false);
//    qDebug() << "selectedSession";
}

void SubjectWidget::selectedSubject(int subject)
{
    nSubject = subject;
    nSession = -1;
    bAddSession->setEnabled(true);
    bRemoveSubject->setEnabled(true);
    bRemoveSession->setEnabled(false);
}

void SubjectWidget::addSubject()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add a subject"), tr("Subject name (code):"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
	experiment->addSubject(text);;
    }
    drawTree();
}

void SubjectWidget::removeSubject()
{
    if(nSubject == -1 || nSubject >= experiment->aSubjects.length() ) { return; }
    delete experiment->aSubjects.takeAt(nSubject);
    drawTree();
}

void SubjectWidget::addSession()
{
    if(nSubject == -1 || nSubject >= experiment->aSubjects.length() ) { return; }
    bool ok;
    QString text = QInputDialog::getText(this, tr("Add a session"), tr("Session name (code):"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
	*(experiment->aSubjects.at(nSubject)->sessions()) << new Session(text,experiment->aSubjects.at(nSubject));
    }
    drawTree();
}

void SubjectWidget::removeSession()
{
    if(nSubject == -1 || nSubject >= experiment->aSubjects.length() || nSession == -1 || nSession >= experiment->aSubjects.at(nSubject)->sessions()->length() ) { return; }
    delete experiment->aSubjects.at(nSubject)->sessions()->takeAt(nSession);
qDebug() << "SubjectWidget::removeSession()";
//    int newSession = qMax(0, nSession - 1);
  //  sessionClicked(nSubject, newSession);

    nSession--;
    qDebug() << "SubjectWidget::removeSession()" << nSession;
    drawTree();
qDebug() << "SubjectWidget::removeSession()";
}


void SubjectWidget::editSubject()
{
    QStringList names = QStringList(*(experiment->getSubjectDataInterpretations()));
    QStringList values = QStringList(*(experiment->aSubjects.at(nSubject)->subjectData()));

    names.insert(0,tr("Name"));
    values.insert(0,experiment->aSubjects.at(nSubject)->name());

    DataEntryWidget *form = new DataEntryWidget(&names,&values,"",0);
    if( form->exec() == QDialog::Accepted)
    {
	experiment->aSubjects.at(nSubject)->setName(values.at(0));
	values.removeAt(0);

	for(int i=0; i< experiment->getSubjectDataInterpretations()->length(); i++)
	{
	    experiment->aSubjects.at(nSubject)->setSubjectData(i,values.at(i));
	}
	drawTree();
    }
}

void SubjectWidget::editSession()
{
    QStringList names = QStringList(*(experiment->getSessionDataInterpretations()));
    QStringList values = QStringList(*(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->sessionData()));

    names.insert(0,tr("Name"));
    values.insert(0,experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->name());

    DataEntryWidget *form = new DataEntryWidget(&names,&values,"",0);
    if( form->exec() == QDialog::Accepted)
    {
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->setName(values.at(0));
	values.removeAt(0);

	for(int i=0; i< experiment->getSessionDataInterpretations()->length(); i++)
	{
	    experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->setSessionData(i,values.at(i));
	}
	drawTree();
    }
}

void SubjectWidget::changeOfImage(int subject, int session, int image)
{
    QString test = QString::number(subject) + "," + QString::number(session);
    for(int i=0; i<whoswho.length(); i++)
    {
	if(whoswho.at(i)==test)
	{
	    tree->setCurrentItem(sessionitems.at(i));
	    break;
	}
    }
}
