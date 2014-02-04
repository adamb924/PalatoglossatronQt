#ifndef LISTEDITORWIDGET_H
#define LISTEDITORWIDGET_H

#include <QWidget>

class QStringList;
class QListView;
class QStringListModel;
class QListWidget;
class QListWidgetItem;

class ListEditorWidget : public QWidget
{
    Q_OBJECT

public:
    ListEditorWidget(QStringList list);
    QStringList stringsList();
private:
    QSize sizeHint() const;
    QListView *view;
    QListWidget *listWidget;
    QStringList list;
public slots:
    void saveNamesFromListWidget();

    void refresh();
    void add();
    void remove();
    void moveup();
    void movedown();
};

#endif // LISTEDITORWIDGET_H
