#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QWidget>
#include <QList>
#include <QTreeWidgetItem>

class Experiment;
class QTreeWidget;
class TreeItem;
class QMouseEvent;
class QLabel;
class QPushButton;

class ImageListWidget : public QWidget
{
Q_OBJECT
public:
    ImageListWidget(QWidget *parent = 0, Experiment *exp=0, int subject=-1, int session=-1);
    QSize sizeHint() const;
    void drawTree();
    void setSubjectSession(int subject, int session);

    QString none,even,odd;

private:
    QTreeWidget *tree;
    QLabel *subjectLabel, *sessionLabel;
    Experiment *experiment;
    int nSubject, nSession, nImage;

    QPushButton *bAddImages, *bRemoveImages;

    QList<QTreeWidgetItem*> imageWidgets;

signals:
    void imageClicked(int subject, int session, int image);
    void imageDoubleClicked(int subject, int session, int image);
    void interlacingChanged();

public slots:
    void activateItem();
    void selectImage(int subject, int session, int index);
private slots:
    void addImages();
    void removeImages();
    void selectionChanged();
    void doubleClick( QTreeWidgetItem * item, int column );
};

#endif // IMAGELISTWIDGET_H
