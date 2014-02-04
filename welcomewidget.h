#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>

class QPushButton;
class QLineEdit;
class QStringListModel;

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    WelcomeWidget(QWidget *parent = 0);
    QSize sizeHint() const;
    QPushButton *create, *open, *exit;

private:

public slots:

};

#endif // WELCOME_H
