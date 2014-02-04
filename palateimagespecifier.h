#ifndef PALATEIMAGESPECIFIER_H
#define PALATEIMAGESPECIFIER_H

#include <QDialog>
#include <QList>

class Session;
class QCheckBox;

class PalateImageSpecifier : public QDialog
{
Q_OBJECT
public:
    explicit PalateImageSpecifier(Session *s, QWidget *parent = 0);
    QList<QCheckBox*> aCheckBoxes;

signals:

private slots:
    void rowSelected(int row);

public slots:

};

#endif // PALATEIMAGESPECIFIER_H
