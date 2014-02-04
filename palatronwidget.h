#ifndef PALATRONWIDGET_H
#define PALATRONWIDGET_H

#include <QWidget>
#include <QTreeWidget>

#include "imagewidget.h"

class QColor;
class QPushButton;
class Experiment;
class QLabel;
class QComboBox;
class QTabWidget;
class QSlider;
class QSpinBox;
class QCheckBox;
class Session;

class PalatronWidget : public QWidget
{
Q_OBJECT
public:
    explicit PalatronWidget(Experiment *exp, QWidget *parent = 0);

    QIcon iconFromColor(QColor col);

    void setDotsTabEnabled(bool enabled);
    void setPalateTabEnabled(bool enabled);
    void setSettingsTabEnabled(bool enabled);
    void setSessionsTabEnabled(bool enabled);
    void addDisplayPlugin(QString str);

private:

    QPushButton *palatronSettingsButton;

    QPushButton *dotColorButton;
    Experiment *experiment;
    QLabel *sessionLabel;
    QComboBox *copyFromSession;
    QComboBox *palateFromSession;
    QTabWidget *tabWidget;

    int selectedPalateImage();

    QTreeWidget *palateImagesWidget;

    Session *session;

    QSlider *toleranceSlider;
    QSpinBox *toleranceSpin;

    QPushButton *drawPalate;

    QSlider *transparencySlider;
    QSpinBox *transparencySpin;
    QPushButton *removePalateImage;

    QComboBox *viewMode;

    QPushButton *bManualUL, *bManualUR, *bManualLL, *bManualLR;

    int nSubject, nSession;

signals:
    void viewChanged(int mode);

    void dotColorChanged(QColor col);
    void sessionChanged(int subj, int sess);

    void toleranceChanged(int tol);
    void transparencyChanged(int trans);

    void defineBoxUL();
    void defineBoxUR();
    void defineBoxLL();
    void defineBoxLR();

    void manualDotUL(bool toggle);
    void manualDotUR(bool toggle);
    void manualDotLL(bool toggle);
    void manualDotLR(bool toggle);

    void selectPalateImages(int subject, int session);
    void resetPalateImages(int subject, int session);

    void palateClicked(int subject, int session, int image);
    void palateDoubleClicked(int subject, int session, int image);

    void dragTransformedView(bool drag);
    void selectFace();

    void pickColor();

    void selectTraceForPalates(int tr);

    void drawThePalate(int subject, int session);
    void refreshPalate();

    void updateSettingsOrPalateFrom();

public slots:
    void choosePalateImages();
    void changeView(ImageWidget::DisplayMode mode);
    void viewComboChanged(int index);
    void updateSession(int subj, int sess);
    void changeOfImage(int subj, int sess, int image);
    void colorPicked(QColor col);
    void launchPalatronSettingsDialog();

private slots:
    void removeImage();
    void palateSelectionChanged();
    void changeTransparency(int tol);
    void changeTolerance(int tol);
    void populateCopyFromSession();
    void populatePalateFromSession();
    void populatePalateImages();
    void defineDotColor();
    void selectCopyFromSession(int index);
    void selectPalateFromSession(int index);
    void drawPalateClicked();

    void activateItem();
    void selectionChanged();
};

#endif // PALATRONWIDGET_H
