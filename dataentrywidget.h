#ifndef DATAENTRYWIDGET_H
#define DATAENTRYWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QList>
#include <QLineEdit>

class QStringList;

class DataEntryWidget : public QDialog
{
Q_OBJECT
public:
    explicit DataEntryWidget(QStringList* f, QStringList* v, QString label, QWidget *parent);

    QList<QLineEdit*> edits;
    QStringList *values;

signals:

public slots:
    void accept();

};

#endif // DATAENTRYWIDGET_H
