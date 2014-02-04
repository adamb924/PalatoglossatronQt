#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

//#include <QWidget>
#include <QScrollArea>
#include <QList>

#include "defaultsettings.h"
#include "experiment.h"
#include "session.h"

class QLabel;
class QImage;
class Image;
class QPoint;
class ExperimentArea;
class QTransform;

class ImageWidget : public QWidget
//class ImageWidget : public QScrollArea
{
Q_OBJECT
Q_ENUMS(DisplayMode)
Q_ENUMS(InputMode)
public:
    explicit ImageWidget(Experiment *exp, QWidget *parent = 0);
    void receiveKeyEvent(QKeyEvent * event);
    void setImage(int subj, int sess, int img);
    void setPalate(int subj, int sess, int img);
    void drawThePalate(int subject, int session);
    void resetPalateImages(int subj,int sess);
    bool LoadImage();
    void refreshPalate();

    QList<QPoint*>* currentTrace() const;

    // zooming
    QTransform zoomTransform;
    int zoomLevel;

    // panning
    QPoint panningOrigin;
    QPoint panOffset;

    enum DisplayMode {
	Untransformed,
	Dot_View,
	Composite_Dot_View,
	TransformedAbstract,
	TransformedTraditional,
	PalateDrawing,
	Plugin
    };

    enum InputMode {
	Point,
	Trace,
	Box_UL,
	Box_UR,
	Box_LL,
	Box_LR,
	Dot_UL,
	Dot_UR,
	Dot_LL,
	Dot_LR,
	ColorPick,
	Grid_Left,
	Grid_Right,
	TransformationPreDrag,
	TransformationDrag,
	SelectFace,
	DrawPalate
    };

    enum ImageType {
	TongueImage,
	Palate
    };

//    QPoint upperLeft, lowerRight;

    void setInvertedImage(bool inverted);

private:
    Image *image;
    Session *session;

    // Drawing functions
    void drawUntransformed(); // will include Dot_View
//    void drawUntransformed(QPainter *painter); // will include Dot_View
    void drawCompositeDotView(QPainter *painter);
    void drawTransformedAbstract(QPainter *painter);
    void drawTransformedTraditional(QPainter *painter);
    void drawMeasureotron(QPainter *painter);

    void autoTrace();

    DisplayMode displayMode, prevDisplayMode;
    InputMode inputMode, prevInputMode;
    ImageType imageType;
    int index;
    int displayPlugin;

    Experiment *experiment;
    ExperimentArea *experimentarea;

    int nSubject, nSession, nImage;

//    void setImage(Image *img);
    void paintEvent(QPaintEvent* event);
    QImage *imageimage, *traditionalTransformed, *compositeView, *faceImage;
    QPoint imageLocation;

    QList<QImage*> aPalateImages;

    bool lButtonDown, mButtonDown;

    void keyReleaseEvent(QKeyEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void processKeyRelease(int key);

    friend class ExperimentArea;

    QSize sizeHint();
    void forceAppropriateSize();

    QColor dotColor;
    int tolerance;


protected:
    void processTracePoint(QPoint pt, Qt::MouseButtons button);

    void wheelEvent ( QWheelEvent * event );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool shift, ctrl, alt;

    bool bDrawInvertedImage;

    QImage *dotViewImage;

    bool bTraceLinesVisible;
    bool bTracePointsVisible;
    bool bPointsVisible;
    bool bPalatronBoxesVisible;
    bool bPalatronDotsVisible;
    bool bGridVisible;

    int nearestGridMark(QPoint pt);

    float nearnessThreshold;

    QPoint firstPlaceClicked, originalOffset;

signals:
    void zoomLevelChanged(int zoomLevel);
    void cursorOverImageChanged(QPoint pos, QColor col);
    void editPointChanged(int pt);
    void editTraceChanged(int tr);
    void statusMessage(QString msg);
    void imageChanged(int subj, int sess, int img);
    void palateChanged(int subj, int sess, int img);
    void colorPicked(QColor col);

    void traceLinesVisibleChanged(bool status);
    void tracePointsVisibleChanged(bool status);
    void pointsVisibleChanged(bool status);
    void palatronBoxesVisibleChanged(bool status);
    void palatronDotsVisibleChanged(bool status);
    void gridVisibleChanged(bool status);

    void viewChanged(ImageWidget::DisplayMode mode);
    void sendGridToTracers();

public slots:
    void dragTransformedView(bool drag);
    void selectFace();

    void changeView(int mode);
    void updateDotView();
    void updateTraditionalTransformed();
    void updateCompositeView();

    void updateTraceLinesVisible(bool status);
    void updateTracePointsVisible(bool status);
    void updatePointsVisible(bool status);
    void updatePalatronBoxesVisible(bool status);
    void updatePalatronDotsVisible(bool status);
    void updateGridVisible(bool status);

    void setEditPoint(int pt);
    void setEditTrace(int tr);
    void nextImage();
    void previousImage();
    void syncSignals();

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

    void pickColor();

    void defineGrid();
    void updateGridLines(int lines);

    void updateIfPluginDislay();
};

#endif // IMAGEWIDGET_H
