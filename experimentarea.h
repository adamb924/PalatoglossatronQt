#ifndef EXPERIMENTAREA_H
#define EXPERIMENTAREA_H

#include <QWidget>
#include <QMdiArea>

#include "defaultsettings.h"
#include "imagewidget.h"

class MainWindow;
class Experiment;
class QDockWidget;
class SubjectWidget;
class ImageListWidget;
class AnnotationWidget;
class PalatronWidget;
class QMdiArea;
class QStatusBar;
class QPoint;
class QLabel;
class QMainWindow;
class QCheckBox;
class QSignalMapper;
class QDockWidget;
class TrackingInterface;
class DisplayInterface;

//class ExperimentArea : public QWidget
class ExperimentArea : public QMdiArea
{
Q_OBJECT
public:
    explicit ExperimentArea(QMainWindow *parent = 0, Experiment *exp=0);
    ~ExperimentArea();
    MainWindow *wnd;
    Experiment *experiment;
    int currentTracing();
    QList<TrackingInterface*>* automaticTracers();
    DisplayInterface* displayPlugin(int i);
    void addDisplayPlugin(QString str);

    QList<QPoint*>* currentTrace() const;

private:
//    QSignalMapper *windowMapper;

    QDockWidget *subjectsDock, *displayDock, *imagesDock, *annotationDock, *palateDock;

//    QDockWidget *subjectsDock;
    SubjectWidget *subjectsWidget;
    ImageListWidget *imagesWidget;
    AnnotationWidget *annotationWidget;
    PalatronWidget *palatronWidget;
    int nSubject, nSession, nTrace, nPoint;

    ImageWidget* activeImageWidget() const;

    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    bool shift, ctrl, alt;

    QStatusBar *statusBar;
    QLabel *statusCursorPosition, *statusColor, *statusZoom;
    QCheckBox *imageInvertedBox;

    DefaultSettings *ds;

    void CreateDocks();
    void CreateStatus();

    QCheckBox *traceLinesVisible;
    QCheckBox *tracePointsVisible;
    QCheckBox *pointsVisible;
    QCheckBox *palatronBoxesVisible;
    QCheckBox *palatronDotsVisible;
    QCheckBox *gridVisible;

signals:
    void repaintAllImageWidgets();
    void sendGridToTracers();

private slots:
    void subwindowActivated();
    void editDisplaySettings();
    void updateTraceLinesVisible(bool status);
    void updateTracePointsVisible(bool status);
    void updatePointsVisible(bool status);
    void updatePalatronBoxesVisible(bool status);
    void updatePalatronDotsVisible(bool status);
    void updateGridVisible(bool status);
    void drawThePalate(int subject, int session);
    void resetPalate(int subject,int session);
    void interlacingChanged();
    void invertedImageAction(bool state);

public slots:
    void displayPluginSettingsUpdated();

    void refreshPalate();
    void setSubjectsDockVisible(bool visible);
    void setDisplayDockVisible(bool visible);
    void setImagesDockVisible(bool visible);
    void setAnnotationsDockVisible(bool visible);
    void setPalatronDockVisible(bool visible);

    void dragTransformedView(bool drag);
    void selectFace();

    void checkDockStatus();

    void RefreshSubjectsDock();
    void RefreshImagesDock();
    void RefreshAnnotationDock();
    void RefreshPalateDock();

    void selectPalateImages(int subject, int session);

    void updateView(int mode);
/*
    void nextImage();
    void previousImage();
*/
    void focusSession(int subject, int session);
    void createImageWindow(int subject, int session, int image);
    void createPalateWindow(int subject, int session, int image);
    void childWindowConnections(ImageWidget *img);

    void selectImage(int subject, int session, int image);
    void selectPalate(int subject, int session, int image);

    void statusBarCursorUpdate(QPoint pos, QColor col);
    void statusBarZoomUpdate(int zoomLevel);

    void defineBoxUL();
    void defineBoxUR();
    void defineBoxLL();
    void defineBoxLR();

    void definePointUL(bool toggle);
    void definePointUR(bool toggle);
    void definePointLL(bool toggle);
    void definePointLR(bool toggle);

    void dotColorChanged(QColor col);
    void toleranceChanged(int tol);
    void showDotView(int show);

    void defineGrid();
    void updateGridLines(int lines);

    void pickColor();
};

#endif // EXPERIMENTAREA_H
