#include "imagewidget.h"
#include "image.h"
#include "trace.h"
#include "point.h"
#include "subject.h"
#include "session.h"
#include "experimentarea.h"
#include "interfaces.h"

#include <QLabel>
#include <QtDebug>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QPoint>
#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QFileInfo>
#include <math.h>
#include <QTransform>
#include <QMessageBox>
#include <QWheelEvent>
#include <QtGlobal>

ImageWidget::ImageWidget(Experiment *exp, QWidget *parent)
{
    experiment = exp;
    experimentarea = qobject_cast<ExperimentArea*>(parent);

    setFocusPolicy(Qt::StrongFocus);

    bDrawInvertedImage = false;

    lButtonDown = false; mButtonDown = false;

    imageType=ImageWidget::TongueImage;

    image = 0;
    imageimage = 0;
    dotViewImage = 0;
    faceImage = 0;
    traditionalTransformed = 0;
    compositeView = 0;

    //    editMode = ImageWidget::Point;
    //    editMode = ImageWidget::Box;
    index = -1;

    zoomLevel = 100;
    panOffset = QPoint(0,0);

    nSubject=-1;
    nSession=-1;
    nImage=-1;

    nearnessThreshold = 0.5f;

    bTraceLinesVisible = true;
    bTracePointsVisible = true;
    bPointsVisible = true;
    bPalatronBoxesVisible = true;
    bPalatronDotsVisible = true;
    bGridVisible = true;

    displayMode = ImageWidget::Untransformed;

    /*
    this->setBackgroundRole(QPalette::Shadow);
    this->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->setUpdatesEnabled(true);
    this->setAttribute(Qt::WA_DeleteOnClose);
*/
    this->setMouseTracking(true);

    shift = false;
    ctrl = false;
    alt = false;

    zoomLevel = 100;

    emit statusMessage(tr("Ready"));

    connect(this,SIGNAL(imageChanged(int,int,int)),this,SLOT(repaint()));
}

QSize ImageWidget::sizeHint()
{
    if(imageimage != 0)
    {
	return imageimage->size();
    }
    else
    {
	return QSize(720,480);
    }
}

void ImageWidget::setImage(int subj, int sess, int img)
{
    if( imageType!=ImageWidget::TongueImage || (subj!=nSubject || sess!=nSession || img!=nImage) )
    {
	QFileInfo info(experiment->aSubjects.at(subj)->sessions()->at(sess)->images()->at(img)->filename());
	if(!info.exists())
	{
	    emit statusMessage(tr("<font color=red>File not found!</font>"));
	    return;
	}

	imageType = ImageWidget::TongueImage;
	nSubject = subj;
	nSession = sess;
	nImage = img;
	image = experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(nImage);
	session = experiment->aSubjects.at(nSubject)->sessions()->at(nSession);
	if( LoadImage() == false )
	{
	    return;
	}

	if(displayMode == ImageWidget::Plugin)
	{
	    if(experimentarea->displayPlugin(displayPlugin) != NULL)
	    {
		experimentarea->displayPlugin(displayPlugin)->calculate(image);
	    }
	}

	this->setFocus(Qt::OtherFocusReason);
	emit imageChanged(nSubject, nSession, nImage);
    }
}

void ImageWidget::setPalate(int subj, int sess, int img)
{
    if( imageType!=ImageWidget::Palate || (subj!=nSubject || sess!=nSession || img!=nImage) )
    {
	imageType = ImageWidget::Palate;
	nSubject = subj;
	nSession = sess;
	nImage = img;
	image = experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palateImages()->at(nImage);
	session = experiment->aSubjects.at(nSubject)->sessions()->at(nSession);
	LoadImage();
	this->setFocus(Qt::OtherFocusReason);
	emit palateChanged(nSubject, nSession, nImage);
    }
}

void ImageWidget::forceAppropriateSize()
{
    if(imageimage==0) { this->parentWidget()->resize(QSize(720,480)); return; }

    QSize newsize;
    newsize.setHeight( this->parentWidget()->frameGeometry().height() - this->parentWidget()->geometry().height() );
    newsize.setWidth( this->parentWidget()->frameGeometry().width() - this->parentWidget()->geometry().width() );
    newsize += imageimage->size();

    //    this->resize(newsize);
    this->parentWidget()->resize(newsize);
}

bool ImageWidget::LoadImage()
{
    qDebug() << "LoadImage begin";
    if(!experiment->validImage(nSubject,nSession,nImage))
    {
	emit statusMessage(tr("<font color=red>Error, invalid image</font>"));
	return false;
    }

    if(imageType==ImageWidget::TongueImage)
    {
	image = experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(nImage);
    }
    else // ImageWidget::Palate
    {
	image = experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palateImages()->at(nImage);
    }

    session = experiment->aSubjects.at(nSubject)->sessions()->at(nSession);

    if(imageimage==0) { imageimage = new QImage(image->filename()); }
    else { imageimage->load(image->filename()); }

    // deinterlace (or not)
    if(imageimage!=0)
	Image::deinterlace(imageimage,image->interlacing(),0);

    // find the dots (once per load)
    image->trackDots();

//    qDebug() << "ImageWidget::LoadImage";

    // dot view (once per load)
    if(displayMode == ImageWidget::Dot_View)
    {
	updateDotView();
    }
    else if(displayMode == ImageWidget::TransformedTraditional)
    {
	updateTraditionalTransformed();
    }

//    qDebug() << "ImageWidget::LoadImage";

    QFileInfo f = QFileInfo(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(nImage)->filename());
    if( f.exists() )
	this->setWindowTitle( experiment->aSubjects.at(nSubject)->name() + " / " +  experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->name() + " / " + f.completeBaseName() );

//    qDebug() << "ImageWidget::LoadImage";

    this->repaint();

    qDebug() << "ImageWidget::LoadImage after";

    return true;
}

void ImageWidget::paintEvent(QPaintEvent* event)
{
    if(imageimage==0) { return; }

    int i;
    int Twidth, Theight;

    QPainter painter(this);
    QTransform transform;
    QTransform notransform;
    notransform.reset();

    qreal zoomScale = (qreal)zoomLevel / 100.0f;

    QTransform tmp = painter.transform();
    tmp.scale(zoomScale , zoomScale);
    tmp.translate( panOffset.x(), panOffset.y() );
    painter.setTransform(tmp);

    QFont scaledFont = painter.font();
    scaledFont.setPointSizeF( qMax( 1.0, 10.0f / zoomScale ));
    painter.setFont(scaledFont); // need to make sure that it's set with point size

    QRectF target, source;
    QRectF facetarget, facesource;
    int xoffset=0, yoffset=0;

    Session *ss = image->settingsSession();
    Session *sp = image->palateSession();

    if(displayMode != ImageWidget::TransformedTraditional)
    {
	if(this->width() < (imageimage->width() * zoomScale))
	    imageLocation.setX( 0 );
	else
	    imageLocation.setX(  ((this->width()-(zoomScale *imageimage->width()) )/ (2*zoomScale) ) );

	if(this->height() < (imageimage->height() * zoomScale))
	    imageLocation.setY( 0 );
	else
	    imageLocation.setY((this->height()-(imageimage->height() * zoomScale))/ (2*zoomScale) );

	// draw the image / background
	target = QRectF(imageLocation.x(),imageLocation.y(),qMin(imageimage->width(),this->width()),qMin(imageimage->height(),this->height()));
	source = QRectF(0,0,qMin(imageimage->width(),this->width()),qMin(imageimage->height(),this->height()));
    }
    else // displayMode == ImageWidget::TransformedTraditional
    {
	// need to deal with the zoom here

	imageLocation.setX(0);
	imageLocation.setY(0);

	Twidth = (int)((double)imageimage->width() *  session->palatronSettingsToUse()->horizontal_distortion_correction);
	Theight = (int)((double)imageimage->height() * session->palatronSettingsToUse()->vertical_distortion_correction);

	xoffset=0; yoffset=0;

	//	qDebug() << "Twidth" << imageimage->width() << Twidth;

	// so.... at this point, traditionalTransformed is a scaled and rotated image
	// the problem is to get the offset correct
	// move it back to the size of the scaled image, as if it were constrained to that size
	xoffset +=  -1 * (traditionalTransformed->width() - Twidth)/2;
	yoffset +=  -1 * (traditionalTransformed->height() - Theight)/2;

	//	qDebug() << "traditionalTransformed" << traditionalTransformed->size();

	//	qDebug() << "normal centering" << xoffset << yoffset;

	// apply the offset
	xoffset += image->xoffset();
	yoffset -= image->yoffset();

	//	qDebug() << "normal palatron" << xoffset << yoffset;

	//	qDebug() << "palatron output" << image->xoffset() << image->yoffset() << image->angle();

	// this was commented out before
	transform.reset();
	transform.translate(xoffset,yoffset);
	painter.setTransform(transform);

	imageLocation.setX(0);
	imageLocation.setY(0);

	// draw the image / background
	target = QRectF(imageLocation.x(),imageLocation.y(),qMin(traditionalTransformed->width(),this->width()-xoffset),qMin(traditionalTransformed->height(),this->height()-yoffset));
	source = QRectF(0,0,qMin(traditionalTransformed->width(),this->width()-xoffset),qMin(traditionalTransformed->height(),this->height()-yoffset));

	facetarget = QRectF(imageLocation.x(),imageLocation.y(),qMin(faceImage->width(),this->width()),qMin(faceImage->height(),this->height()));
	facesource = QRectF(0,0,qMin(faceImage->width(),this->width()),qMin(faceImage->height(),this->height()));

	/*
	qDebug() << "traditionalTransformed" << traditionalTransformed->size();
    	qDebug() << "offsets" << xoffset << yoffset;
	qDebug() << this->width() << this->height();
	qDebug() << "target" << target;
	qDebug() << "source" << source;
	qDebug() << "facetarget" << facetarget;
	qDebug() << "facesource" << facesource;
*/
    }

    //    int i;
    switch(displayMode)
    {
    case ImageWidget::Dot_View:
	if(dotViewImage != 0)
	    painter.drawImage(target, *(dotViewImage), source);
	break;
    case ImageWidget::TransformedAbstract:
	painter.fillRect(this->rect(),experiment->ds->cTransformedAbstractBg);
	break;
    case ImageWidget::TransformedTraditional:
	if(traditionalTransformed != 0)
	    painter.drawImage(target, *(traditionalTransformed), source);
	painter.setTransform(notransform);
	//	if(faceImage!= 0)
	//	    painter.drawImage(facetarget, *(faceImage), facesource);
	break;
    case ImageWidget::Composite_Dot_View:
	//	qDebug() << "about to draw";
	if(compositeView != 0)
	{
	    //	    qDebug() << "drawing";
	    painter.drawImage(target, *(compositeView), source);
	    //	    qDebug() << "finished drawing";
	}
	break;
    case ImageWidget::PalateDrawing:
	imageLocation.setX(0);
	imageLocation.setY(0);

	//	qDebug() << "case ImageWidget::PalateDrawing:";

	if(session->palateImages()->count() != aPalateImages.count())
	{
	    resetPalateImages(nSubject,nSession);
	}
	for(i=0; i<session->palateImages()->count(); i++)
	{
	    //	    session->palateImages()->

	    Twidth = (int)((double)imageimage->width() * session->palatronSettingsToUse()->horizontal_distortion_correction);
	    Theight = (int)((double)imageimage->height() * session->palatronSettingsToUse()->vertical_distortion_correction);

	    xoffset=0; yoffset=0;

	    xoffset +=  -1 * (aPalateImages.at(i)->width() - Twidth)/2;
	    yoffset +=  -1 * (aPalateImages.at(i)->height() - Theight)/2;

	    //	    qDebug() << "overlay" << aPalateImages.at(i)->size();

	    //	    qDebug() << "overlay centering" << xoffset << yoffset;

	    // apply the offset
	    xoffset += session->palateImages()->at(i)->xoffset();
	    yoffset -= session->palateImages()->at(i)->yoffset();

	    //	    qDebug() << "overlay palatron" << xoffset << yoffset;

	    transform.reset();
	    transform.translate(xoffset,yoffset);
	    painter.setTransform(transform);

	    target = QRectF(imageLocation.x(),imageLocation.y(),qMin(aPalateImages.at(i)->width(),this->width()-xoffset),qMin(aPalateImages.at(i)->height(),this->height()-yoffset));
	    source = QRectF(0,0,qMin(aPalateImages.at(i)->width(),this->width()-xoffset),qMin(aPalateImages.at(i)->height(),this->height()-yoffset));

	    //	    qDebug() << "opacity" << 1.0f - session->palateTransparencies()->at(i)/100.0f;
	    painter.setOpacity(1.0f - session->palateTransparencies()->at(i)/100.0f);
	    painter.drawImage(target, *(aPalateImages.at(i)), source);
	}

	break;
    case ImageWidget::Plugin:
	break;
    default:
	if(imageimage != 0)
	{
	    if(bDrawInvertedImage)
	    {
		QImage invertedImage = imageimage->copy();
		invertedImage.invertPixels();
		painter.drawImage(target, invertedImage, source);
	    }
	    else
	    {
		painter.drawImage(target, *imageimage, source);
	    }
	}
	break;
    }

    int j;
    QPoint pt;
    QRect rct;

    if(displayMode==ImageWidget::Untransformed || displayMode==ImageWidget::Dot_View)
    {
	// draw Grid
	if(bGridVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cFan,Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	    for(i=0; i<experiment->grid()->length(); i++)
	    {
		painter.drawLine(experiment->grid()->at(i).translated(imageLocation));
	    }

	    if(inputMode == ImageWidget::Grid_Left || inputMode == ImageWidget::Grid_Right )
	    {
		if( experiment->fanLeft()->p1() != QPoint(-1,-1) )
		{
		    painter.drawLine(experiment->fanLeft()->translated(imageLocation));
		}
	    }
	    if(inputMode == ImageWidget::Grid_Right)
	    {
		if( experiment->fanRight()->p1() != QPoint(-1,-1) )
		{
		    painter.drawLine(experiment->fanRight()->translated(imageLocation));
		}
	    }
	}

	// draw points
	if(bPointsVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cMeasurementPoint,Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	    painter.setBrush(QBrush(experiment->ds->cMeasurementPoint,Qt::SolidPattern));
	    for(i=0; i<image->points()->length(); i++)
	    {
		if(image->points()->at(i)->x()!=-1 && image->points()->at(i)->y()!=-1)
		{
		    pt = *(image->points()->at(i)->pt()) + imageLocation;
		    int dim = qMax(1, (int)(experiment->ds->nMeasurementPointSize/zoomScale));
		    painter.drawEllipse((QPoint)pt,dim,dim);

		    // draw a label
		    // eventually make this optional
		    painter.drawText( pt + QPoint(experiment->ds->nMeasurementPointSize/zoomScale,-1*experiment->ds->nMeasurementPointSize/zoomScale), experiment->getPointInterpretations()->at(i) );
		}
	    }
	}

	// draw trace lines
	if(bTraceLinesVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cTraceLine,Qt::SolidPattern),experiment->ds->nTraceWidth/zoomScale,Qt::SolidLine));
	    for(i=0; i<image->traces()->length(); i++)
	    {
		for(j=1; j< image->traces()->at(i)->points()->length(); j++)
		{
		    if(*(image->traces()->at(i)->points()->at(j)) != QPoint(-1,-1) && *(image->traces()->at(i)->points()->at(j-1)) != QPoint(-1,-1) )
		    {
			painter.drawLine(*(image->traces()->at(i)->points()->at(j-1))+imageLocation,*(image->traces()->at(i)->points()->at(j))+imageLocation);
		    }
		}
	    }
	}

	// draw trace points
	if(bTracePointsVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cTraceDot,Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	    painter.setBrush(QBrush(experiment->ds->cTraceDot,Qt::SolidPattern));
	    for(i=0; i<image->traces()->length(); i++)
	    {
		for(j=0; j< image->traces()->at(i)->points()->length(); j++)
		{
		    if(*(image->traces()->at(i)->points()->at(j)) != QPoint(-1,-1))
		    {
			pt = *(image->traces()->at(i)->points()->at(j))+imageLocation;
			int dim = qMax(1, (int)(experiment->ds->nTraceDotSize/zoomScale));
			painter.drawEllipse(pt,dim,dim);
		    }
		}
	    }
	}

	// draw Palatron dots
	if(bPalatronDotsVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cPalatronDot,Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	    painter.setBrush(QBrush(experiment->ds->cPalatronDot,Qt::SolidPattern));
	    int dim = qMax(1, (int)(experiment->ds->nPalatronDotSize/zoomScale));
	    if( *(image->ul()) != QPoint(-1,-1) )
	    {
		pt = *(image->ul()) + imageLocation;
		painter.drawEllipse(pt,dim,dim);
	    }
	    if( *(image->ur()) != QPoint(-1,-1) )
	    {
		pt = *(image->ur()) + imageLocation;
		painter.drawEllipse(pt,dim,dim);
	    }
	    if( *(image->ll()) != QPoint(-1,-1) )
	    {
		pt = *(image->ll()) + imageLocation;
		painter.drawEllipse(pt,dim,dim);
	    }
	    if( *(image->lr()) != QPoint(-1,-1) )
	    {
		pt = *(image->lr()) + imageLocation;
		painter.drawEllipse(pt,dim,dim);
	    }
	}
    }

    if(displayMode==ImageWidget::Untransformed || displayMode==ImageWidget::Dot_View || displayMode==ImageWidget::Composite_Dot_View )
    {
	// draw Palatron boxes
	if(bPalatronBoxesVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cPalatronBox,Qt::SolidPattern),experiment->ds->nPalatronBoxWidth/zoomScale,Qt::SolidLine));
	    painter.setBrush(Qt::NoBrush);

	    if( ss->ul()->topLeft() != QPoint(-1,-1) && ss->ul()->bottomRight() != QPoint(-1,-1) )
	    {
		rct = *(ss->ul());
		rct.moveTopLeft(rct.topLeft() + imageLocation);
		painter.drawRect(rct);
	    }
	    if( ss->ur()->topLeft() != QPoint(-1,-1) && ss->ul()->bottomRight() != QPoint(-1,-1) )
	    {
		rct = *(ss->ur());
		rct.moveTopLeft(rct.topLeft() + imageLocation);
		painter.drawRect(rct);
	    }
	    if( ss->ll()->topLeft() != QPoint(-1,-1) && ss->ll()->bottomRight() != QPoint(-1,-1) )
	    {
		rct = *(ss->ll());
		rct.moveTopLeft(rct.topLeft() + imageLocation);
		painter.drawRect(rct);
	    }
	    if( ss->lr()->topLeft() != QPoint(-1,-1) && ss->lr()->bottomRight() != QPoint(-1,-1) )
	    {
		rct = *(ss->lr());
		rct.moveTopLeft(rct.topLeft() + imageLocation);
		painter.drawRect(rct);
	    }
	}
    }

    if(displayMode==ImageWidget::TransformedAbstract)
    {
	transform.reset();
	painter.setTransform(transform);

	imageLocation = QPoint(0,0);

	// draw points
	if(bPointsVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cMeasurementPoint,Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	    painter.setBrush(QBrush(experiment->ds->cMeasurementPoint,Qt::SolidPattern));
	    for(i=0; i<image->points()->length(); i++)
	    {
		if(image->points()->at(i)->Tx()!=-1 && image->points()->at(i)->Ty()!=-1)
		{
		    pt = *(image->points()->at(i)->ptTransformed()) + imageLocation;
		    int dim = qMax(1, (int)(experiment->ds->nMeasurementPointSize/zoomScale));
		    painter.drawEllipse(pt,dim,dim);
		}
	    }
	}

	// draw trace lines
	if(bTraceLinesVisible)
	{
	    painter.setPen(QPen(QBrush(experiment->ds->cTraceLine,Qt::SolidPattern),experiment->ds->nTraceWidth/zoomScale,Qt::SolidLine));
	    for(i=0; i<image->traces()->length(); i++)
	    {
		for(j=1; j< image->traces()->at(i)->pointsTransformed()->length(); j++)
		{
		    painter.drawLine(*(image->traces()->at(i)->pointsTransformed()->at(j-1))+imageLocation,*(image->traces()->at(i)->pointsTransformed()->at(j))+imageLocation);
		}
	    }
	}

	// draw trace points
	if(bTracePointsVisible)
	{
	    bool visible = false;
	    painter.setPen(QPen(QBrush(experiment->ds->cTraceLine,Qt::SolidPattern),experiment->ds->nTraceWidth/zoomScale,Qt::SolidLine));
	    painter.setBrush(QBrush(experiment->ds->cTraceDot,Qt::SolidPattern));
	    for(i=0; i<image->traces()->length(); i++)
	    {
		for(j=0; j< image->traces()->at(i)->pointsTransformed()->length(); j++)
		{
		    pt = *(image->traces()->at(i)->pointsTransformed()->at(j))+imageLocation;
		    int dim = qMax(1, (int)(experiment->ds->nTraceDotSize/zoomScale));
		    painter.drawEllipse(pt,dim,dim);
		    if( pt.x() > 0 && pt.y() > 0 && pt.x() < this->width() && pt.y() < this->height() ) { visible = true; }
		}
	    }
	    if( !visible )
	    {
		if(image->traces()->at(0)->pointsTransformed()->length() > 0)
		{
		    pt = *(image->traces()->at(0)->pointsTransformed()->at(0))+imageLocation;
		    painter.drawText ( 0, this->height()/2 , "There is a point at ("+QString::number(pt.x())+","+QString::number(pt.y())+")." );
		}
	    }
	}
    }


    if(inputMode == ImageWidget::SelectFace)
    {
	painter.setPen(QPen(QBrush(QColor(255,255,255),Qt::SolidPattern),1/zoomScale,Qt::SolidLine));
	painter.setBrush(Qt::NoBrush);
	painter.drawLine( QPoint(session->palatronSettingsToUse()->faceLocation, 0)+imageLocation , QPoint(session->palatronSettingsToUse()->faceLocation, imageimage->height() ) +imageLocation );
    }

    // draw the palate
    if(displayMode == ImageWidget::PalateDrawing || displayMode == ImageWidget::TransformedTraditional || displayMode == ImageWidget::TransformedAbstract)
    {
	imageLocation.setX(0);
	imageLocation.setY(0);

	// if this works, remove all reference to the offset
	QPoint offset(0,0);

	painter.setTransform(notransform);

	// draw lines
	painter.setPen(QPen(QBrush(experiment->ds->cTraceLine,Qt::SolidPattern),experiment->ds->nTraceWidth/zoomScale,Qt::SolidLine));
	for(j=1; j< sp->palate()->points()->length(); j++)
	{
	    painter.drawLine(*(sp->palate()->points()->at(j-1))+imageLocation-offset,*(sp->palate()->points()->at(j))+imageLocation-offset);
	}
	painter.setPen(QPen(QBrush(experiment->ds->cTraceLine,Qt::SolidPattern),experiment->ds->nTraceWidth/zoomScale,Qt::SolidLine));
	painter.setBrush(QBrush(experiment->ds->cTraceDot,Qt::SolidPattern));
	for(j=0; j< sp->palate()->points()->length(); j++)
	{
	    pt = *(sp->palate()->points()->at(j))+imageLocation-offset;
	    int dim = qMax(1, (int)(experiment->ds->nTraceDotSize/zoomScale));
	    painter.drawEllipse(pt,dim,dim);
	}
    }

    if(displayMode == ImageWidget::Plugin)
    {
	if(experimentarea->displayPlugin(displayPlugin) != NULL)
	{
	    experimentarea->displayPlugin(displayPlugin)->paint(&painter);
	}
    }

}

void ImageWidget::drawUntransformed()
{
}

void ImageWidget::drawCompositeDotView(QPainter *painter)
{
    qDebug() << "drawCompositeDotView";

}

void ImageWidget::drawTransformedAbstract(QPainter *painter)
{
    qDebug() << "drawTransformedAbstract";
    //case ImageWidget::TransformedAbstract:
    painter->fillRect(this->rect(),experiment->ds->cTransformedAbstractBg);
    //    break;

}

void ImageWidget::drawTransformedTraditional(QPainter *painter)
{
    qDebug() << "drawTransformedTraditional";

}

void ImageWidget::drawMeasureotron(QPainter *painter)
{
    qDebug() << "drawMeasureotron";

}

void ImageWidget::wheelEvent ( QWheelEvent * event )
{
    zoomLevel += 10 * event->delta()/120;

    emit zoomLevelChanged(zoomLevel);

    this->repaint();
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint pt = (((event->pos()-panOffset*(zoomLevel / 100.0f)) / (zoomLevel / 100.0f)) - imageLocation);

    if( event->button() != Qt::MidButton)
    {
	lButtonDown = true;

	switch(inputMode)
	{
	case ImageWidget::Trace:
	    processTracePoint(pt,event->buttons());
	    break;
	case ImageWidget::DrawPalate:
	    processTracePoint(pt,event->buttons());
	    break;
	case ImageWidget::Box_UL:
	    session->ul()->setTopLeft(pt);
	    session->ul()->setBottomRight(QPoint(-1,-1));
	    break;
	case ImageWidget::Box_UR:
	    session->ur()->setTopLeft(pt);
	    session->ur()->setBottomRight(QPoint(-1,-1));
	    break;
	case ImageWidget::Box_LL:
	    session->ll()->setTopLeft(pt);
	    session->ll()->setBottomRight(QPoint(-1,-1));
	    break;
	case ImageWidget::Box_LR:
	    session->lr()->setTopLeft(pt);
	    session->lr()->setBottomRight(QPoint(-1,-1));
	    break;
	case ImageWidget::Grid_Left:
	    experiment->fanLeft()->setP1(pt);
	    break;
	case ImageWidget::Grid_Right:
	    experiment->fanRight()->setP1(pt);
	    break;
	case ImageWidget::TransformationPreDrag:
	    originalOffset = QPoint(session->palatronSettingsToUse()->OverlayX, session->palatronSettingsToUse()->OverlayY);
	    firstPlaceClicked = pt;
	    inputMode = ImageWidget::TransformationDrag;
	    this->setCursor(QCursor(Qt::ClosedHandCursor));
	    break;
	default:
	    break;
	}
    }
    else if( event->button() == Qt::MidButton)
    {
	mButtonDown = true;

	panningOrigin = pt;
    }
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(imageimage == 0) { return; }

    QPoint pt = (((event->pos()-panOffset*(zoomLevel / 100.0f)) / (zoomLevel / 100.0f)) - imageLocation);

    if( event->button() != Qt::MidButton)
    {
	lButtonDown = false;
	if(event->button()!=Qt::LeftButton) { return; }

	if(index==-1)
	{
	    emit statusMessage(tr("You haven't selected an annotation to edit."));
	    return;
	}

	switch(inputMode)
	{
	case ImageWidget::Trace:
	    /*	// this seems to be misplaced
	    if(shift)
	    {
		if(experiment->getTraceType(index)==Experiment::Free)
		{
		    image->deleteFromEdge(index,image->pointNearest(index,pt));
		    update();
		}
	    }
	    emit statusMessage(tr("Ready"));
    */
	    break;
	case ImageWidget::Point:
	    image->setPoint(index,pt);
	    update();
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Box_UL:
	    session->ul()->setBottomRight(pt);
	    image->trackDots();
	    image->palatron();
	    inputMode = prevInputMode;
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Box_UR:
	    session->ur()->setBottomRight(pt);
	    image->trackDots();
	    image->palatron();
	    inputMode = prevInputMode;
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Box_LL:
	    session->ll()->setBottomRight(pt);
	    image->trackDots();
	    image->palatron();
	    inputMode = prevInputMode;
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Box_LR:
	    session->lr()->setBottomRight(pt);
	    image->trackDots();
	    image->palatron();
	    inputMode = prevInputMode;
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Dot_UL:
	    image->ul()->setX(pt.x());
	    image->ul()->setY(pt.y());
	    inputMode = prevInputMode;
	    image->palatron();
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Dot_UR:
	    image->ur()->setX(pt.x());
	    image->ur()->setY(pt.y());
	    inputMode = prevInputMode;
	    image->palatron();
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Dot_LL:
	    image->ll()->setX(pt.x());
	    image->ll()->setY(pt.y());
	    inputMode = prevInputMode;
	    image->palatron();
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Dot_LR:
	    image->lr()->setX(pt.x());
	    image->lr()->setY(pt.y());
	    inputMode = prevInputMode;
	    image->palatron();
	    this->repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::ColorPick:
	    if(!( pt.x()<0 || pt.y()<0 || pt.y()>=imageimage->height() || pt.x()>=imageimage->width()) )
	    {
		emit colorPicked(QColor(imageimage->pixel(pt)));
		emit statusMessage(tr("Ready"));
		this->setCursor(QCursor(Qt::ArrowCursor));
		inputMode = prevInputMode;
	    }
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Grid_Left:
	    experiment->fanLeft()->setP2(pt);
	    repaint();
	    emit statusMessage(tr("Drag a line to define the right boundary of the fan"));
	    inputMode = ImageWidget::Grid_Right;
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::Grid_Right:
	    experiment->fanRight()->setP2(pt);
	    experiment->updateGrid();
	    emit sendGridToTracers();
	    inputMode = prevInputMode;
	    repaint();
	    emit statusMessage(tr("Ready"));
	    break;
	case ImageWidget::SelectFace:
	    inputMode = prevInputMode;
	    break;
	case ImageWidget::DrawPalate:
	    break;
	default: // this is weird code to have in the default case
	    inputMode = ImageWidget::TransformationPreDrag;
	    this->setCursor(QCursor(Qt::OpenHandCursor));
	    break;
	}
    }
    else if( event->button() == Qt::MidButton)
    {
	mButtonDown = false;
	panningOrigin = QPoint(-1,-1);
    }
}

void ImageWidget::processTracePoint(QPoint pt, Qt::MouseButtons button)
{
    int res;

    if(inputMode == ImageWidget::DrawPalate)
    {
	if(button == Qt::RightButton)
	    session->palate()->removePoint(pt);
	else
	    session->addToPalateTrace(pt);
    }
    else
    {
	switch(experiment->getTraceType(index))
	{
	case Experiment::Free:
	    if(button == Qt::RightButton)
		image->traces()->at(index)->removePoint(pt);
	    else
		image->addToTrace(index,pt);
	    break;
	case Experiment::Grid:
	    if( experiment->grid()==0 || experiment->grid()->length() == 0 )
	    {
		emit statusMessage(tr("Error: no grid has been defined for this experiment. Either define a grid or switch to free-trace mode."));
	    }
	    res = nearestGridMark(pt);
	    if(res!=-1)
	    {
		if(shift)
		{
		    image->deleteFromEdge(index,res);
		}
		else
		{
		    if(button == Qt::RightButton)
			image->traces()->at(index)->nullifyPoint(res);
		    else
			image->setTracePoint(index,res,pt);
		}
	    }
	    break;
	default:
	    break;
	}
    }
    repaint();
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(imageimage == 0) { return; }

    QPoint pt = (((event->pos()-panOffset*(zoomLevel / 100.0f)) / (zoomLevel / 100.0f)) - imageLocation);
    if(pt.x()<0 || pt.y()<0 || pt.y()>=imageimage->height() || pt.x()>=imageimage->width())
    {
	pt.setX(-1);
	pt.setY(-1);
	emit cursorOverImageChanged(pt,QColor(0,0,0,0)); // using alpha as an error value
	return;
    }
    emit cursorOverImageChanged(pt,QColor(imageimage->pixel(pt)));

    if(inputMode == ImageWidget::SelectFace)
    {
	session->palatronSettingsToUse()->faceLocation = pt.x();
	repaint();
    }

    if( mButtonDown && panningOrigin != QPoint(-1,-1) )
    {
	panOffset += pt - panningOrigin;
	repaint();
    }

    //////////////////////////////////////////////
    // now things that only have a mouse button //
    //////////////////////////////////////////////
    if(!lButtonDown) { return; }

    if(index==-1)
    {
	emit statusMessage(tr("You haven't selected an annotation to edit."));
	return;
    }

    QPoint offset;

    switch(inputMode)
    {
    case ImageWidget::Trace:
	processTracePoint(pt,event->buttons());
	break;
    case ImageWidget::Point:
	image->setPoint(index,pt);
	update();
	break;
    case ImageWidget::Box_UL:
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->ul()->setBottomRight(pt);
	repaint();
	break;
    case ImageWidget::Box_UR:
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->ur()->setBottomRight(pt);
	repaint();
	break;
    case ImageWidget::Box_LL:
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->ll()->setBottomRight(pt);
	repaint();
	break;
    case ImageWidget::Box_LR:
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->lr()->setBottomRight(pt);
	repaint();
	break;
    case ImageWidget::Grid_Left:
	if( experiment->fanLeft()->p1() != QPoint(-1,-1) )
	{
	    experiment->fanLeft()->setP2(pt);
	    repaint();
	}
	break;
    case ImageWidget::Grid_Right:
	if( experiment->fanRight()->p1() != QPoint(-1,-1) )
	{
	    experiment->fanRight()->setP2(pt);
	    repaint();
	}
	break;
    case ImageWidget::TransformationDrag:
	offset = pt - firstPlaceClicked;
	session->palatronSettingsToUse()->OverlayX = originalOffset.x() + offset.x();
	session->palatronSettingsToUse()->OverlayY = originalOffset.y() - offset.y();
	/*
	for(i=0; i<session->palate()->points()->count(); i++)
	{
	    *(session->palate()->points()->at(i)) += QPoint(offset.x(),-1 * offset.y());
	}
*/
	image->palatron();
	repaint();
	break;
    case ImageWidget::DrawPalate:
	processTracePoint(pt,event->buttons());
	break;
    default:
	break;
    }
}

void ImageWidget::setEditPoint(int pt)
{
    if(image==0 || pt<0 || pt >= image->points()->length()) { return; }

    //    qDebug() << "setEditPoint" << pt;

    if( inputMode != ImageWidget::Point || index != pt )
    {
	inputMode = ImageWidget::Point;
	index = pt;
	emit editPointChanged(pt);
	emit statusMessage(tr("Ready"));
    }
}

void ImageWidget::setEditTrace(int trace)
{
    if(image==0 || trace<0 || trace >= image->traces()->length()) { return; }

    if( inputMode != ImageWidget::Trace || index != trace )
    {
	this->inputMode = ImageWidget::Trace;
	this->index = trace;
	emit editTraceChanged(index);
	emit statusMessage(tr("Ready"));
    }
}

void ImageWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    case Qt::Key_Shift:
	shift=1;
	break;
    case Qt::Key_Control:
	ctrl=1;
	break;
    case Qt::Key_Alt:
	alt=1;
	break;
    case Qt::Key_Right:
	//	qDebug() << "right";
	nextImage();
	break;
    case Qt::Key_Left:
	//	qDebug() << "left";
	previousImage();
	break;
    }
}

void ImageWidget::keyReleaseEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Shift:
	shift=0;
	break;
    case Qt::Key_Control:
	ctrl=0;
	break;
    case Qt::Key_Alt:
	alt=0;
	break;
    }
    processKeyRelease(event->key());

}

void ImageWidget::receiveKeyEvent(QKeyEvent * event)
{
    switch(event->key())
    {
    case Qt::Key_Shift:
	shift=0;
	break;
    case Qt::Key_Control:
	ctrl=0;
	break;
    case Qt::Key_Alt:
	alt=0;
	break;
    default:
	break;
    }

    processKeyRelease(event->key());

}

void ImageWidget::processKeyRelease(int key)
{
    switch(key)
    {
    case Qt::Key_X:
	if(inputMode == ImageWidget::DrawPalate)
	{
	    session->clearPalateTrace();
	    repaint();
	    break;
	}
	if(this->index != -1)
	{
	    switch(inputMode)
	    {
	    case ImageWidget::Trace:
		image->removeTrace(index);
		update();
		//		qDebug() << "Trace";
		break;
	    case ImageWidget::Point:
		image->removePoint(index);
		update();
		//		qDebug() << "Point";
		break;
	    default:
		//		qDebug() << "Default";
		break;
	    }
	}
	break;
    case Qt::Key_Escape:
	//	inputMode = // something
	break;
    case Qt::Key_1:
	setEditTrace(0);
	break;
    case Qt::Key_2:
	setEditTrace(1);
	break;
    case Qt::Key_3:
	setEditTrace(2);
	break;
    case Qt::Key_4:
	setEditTrace(3);
	break;
    case Qt::Key_5:
	setEditTrace(4);
	break;
    case Qt::Key_6:
	setEditTrace(5);
	break;
    case Qt::Key_7:
	setEditTrace(6);
	break;
    case Qt::Key_8:
	setEditTrace(7);
	break;
    case Qt::Key_9:
	setEditTrace(8);
	break;
    case Qt::Key_0:
	setEditTrace(9);
	break;
    case Qt::Key_F1:
	setEditPoint(0);
	break;
    case Qt::Key_F2:
	setEditPoint(1);
	break;
    case Qt::Key_F3:
	setEditPoint(2);
	break;
    case Qt::Key_F4:
	setEditPoint(3);
	break;
    case Qt::Key_F5:
	setEditPoint(4);
	break;
    case Qt::Key_F6:
	setEditPoint(5);
	break;
    case Qt::Key_F7:
	setEditPoint(6);
	break;
    case Qt::Key_F8:
	setEditPoint(7);
	break;
    case Qt::Key_F9:
	setEditPoint(8);
	break;
    case Qt::Key_F10:
	setEditPoint(9);
	break;
    case Qt::Key_F11:
	setEditPoint(10);
	break;
    case Qt::Key_F12:
	setEditPoint(11);
	break;
    case Qt::Key_A:
	autoTrace();
	break;
    }
    emit statusMessage(tr("Ready"));
}

void ImageWidget::nextImage()
{
    nImage++;
    if( experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->length() == nImage )
    {
	nImage = 0;
    }
    LoadImage();
    emit imageChanged(nSubject, nSession, nImage);
}

void ImageWidget::previousImage()
{
    nImage--;
    if( -1 == nImage )
    {
	nImage = experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->length() - 1;
    }
    LoadImage();
    emit imageChanged(nSubject, nSession, nImage);
}

void ImageWidget::syncSignals()
{
    switch(inputMode)
    {
    case ImageWidget::Trace:
	emit editTraceChanged(index);
	break;
    case ImageWidget::Point:
	emit editPointChanged(index);
	break;
    default:
	break;
    }
    emit statusMessage(tr("Ready"));

    emit imageChanged(nSubject,nSession,nImage);
    emit traceLinesVisibleChanged(bTraceLinesVisible);
    emit tracePointsVisibleChanged(bTracePointsVisible);
    emit pointsVisibleChanged(bPointsVisible);
    emit palatronBoxesVisibleChanged(bPalatronBoxesVisible);
    emit palatronDotsVisibleChanged(bPalatronDotsVisible);
    emit gridVisibleChanged(bGridVisible);
    emit viewChanged(displayMode);
}

void ImageWidget::defineBoxUL()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::Box_UL;
    emit statusMessage(tr("Define the upper left dot-tracking box (click-and-drag from the upper left to the lower right corner)"));
}

void ImageWidget::defineBoxUR()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::Box_UR;
    emit statusMessage(tr("Define the upper right dot-tracking box (click-and-drag from the upper left to the lower right corner)"));
}

void ImageWidget::defineBoxLL()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::Box_LL;
    emit statusMessage(tr("Define the lower left dot-tracking box (click-and-drag from the upper left to the lower right corner)"));
}

void ImageWidget::defineBoxLR()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::Box_LR;
    emit statusMessage(tr("Define the lower right dot-tracking box (click-and-drag from the upper left to the lower right corner)"));
}

void ImageWidget::definePointUL(bool toggle)
{
    if(toggle)
    {
	image->setMul(true);
	if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
	prevInputMode = inputMode;
	inputMode = ImageWidget::Dot_UL;
	emit statusMessage(tr("Define the upper left dot-tracking dot by clicking in the desired location."));
    }
    else
    {
	image->setMul(false);
	image->ul()->setX(-1);
	image->ul()->setY(-1);
	image->trackDots();
	image->palatron();
	update();
    }
}

void ImageWidget::definePointUR(bool toggle)
{
    if(toggle)
    {
	image->setMur(true);
	if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
	prevInputMode = inputMode;
	inputMode = ImageWidget::Dot_UR;
	emit statusMessage(tr("Define the upper right dot-tracking dot by clicking in the desired location."));
    }
    else
    {
	image->setMur(false);
	image->ur()->setX(-1);
	image->ur()->setY(-1);
	image->trackDots();
	image->palatron();
	update();
    }
}

void ImageWidget::definePointLL(bool toggle)
{
    if(toggle)
    {
	image->setMll(true);
	if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
	prevInputMode = inputMode;
	inputMode = ImageWidget::Dot_LL;
	emit statusMessage(tr("Define the lower left dot-tracking dot by clicking in the desired location."));
    }
    else
    {
	image->setMll(false);
	image->ll()->setX(-1);
	image->ll()->setY(-1);
	image->trackDots();
	image->palatron();
	update();
    }
}

void ImageWidget::definePointLR(bool toggle)
{
    if(toggle)
    {
	image->setMlr(true);
	if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
	prevInputMode = inputMode;
	inputMode = ImageWidget::Dot_LR;
	emit statusMessage(tr("Define the lower right dot-tracking dot by clicking in the desired location."));
    }
    else
    {
	image->setMlr(false);
	image->lr()->setX(-1);
	image->lr()->setY(-1);
	image->trackDots();
	image->palatron();
	update();
    }
}

void ImageWidget::dotColorChanged(QColor col)
{
    image->trackDots();
    image->palatron();
    if(displayMode== ImageWidget::Dot_View)
    {
	updateDotView();
    }
    this->repaint();
}

void ImageWidget::toleranceChanged(int tol)
{
    image->trackDots();
    image->palatron();
    if(displayMode== ImageWidget::Dot_View)
    {
	updateDotView();
    }
    this->repaint();
}

void ImageWidget::showDotView(int show)
{
    if(show)
    {
	prevDisplayMode = displayMode;
	updateDotView();
	image->trackDots();
	image->palatron();
	displayMode = ImageWidget::Dot_View;
    }
    else
    {
	displayMode = prevDisplayMode;
    }
    update();
}

void ImageWidget::pickColor()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::ColorPick;
    emit statusMessage(tr("Click on a color to select that color."));
    this->setCursor(QCursor(Qt::CrossCursor));
}

void ImageWidget::updateTraceLinesVisible(bool status)
{
    bTraceLinesVisible = status;
    repaint();
}

void ImageWidget::updateTracePointsVisible(bool status)
{
    bTracePointsVisible = status;
    repaint();
}

void ImageWidget::updatePointsVisible(bool status)
{
    bPointsVisible = status;
    repaint();
}

void ImageWidget::updatePalatronBoxesVisible(bool status)
{
    bPalatronBoxesVisible = status;
    repaint();
}

void ImageWidget::updatePalatronDotsVisible(bool status)
{
    bPalatronDotsVisible = status;
    repaint();
}

void ImageWidget::updateGridVisible(bool status)
{
    bGridVisible = status;
    repaint();
}


void ImageWidget::changeView(int mode)
{
    if(mode < 1000)
    {
	if(mode==ImageWidget::TransformedTraditional || mode==ImageWidget::TransformedAbstract)
	{
	    if(!image->palatron()) { QMessageBox::critical(this,"PalatoglossatronQt Error","Palatron could not be run on this image because one or more of the dots was not found. Either the image is bad or you need to redefine the dot-tracking boxes (the Palatron boxes)."); }
	}

	if(mode==ImageWidget::TransformedTraditional)
	{
	    updateTraditionalTransformed();
	}
	else if(mode == ImageWidget::Dot_View)
	{
	    updateDotView();
	}
	else if(mode == ImageWidget::Composite_Dot_View)
	{
	    updateCompositeView();
	}

	prevDisplayMode = displayMode;
	displayMode = (DisplayMode)mode;
    }
    else
    {
	displayMode = ImageWidget::Plugin;
	displayPlugin = mode - 1000;

	if(displayMode == ImageWidget::Plugin)
	{
	    if(experimentarea->displayPlugin(displayPlugin) != NULL)
	    {
		experimentarea->displayPlugin(displayPlugin)->calculate(image);
	    }
	}
    }
    repaint();
}

void ImageWidget::defineGrid()
{
    experiment->fanLeft()->setLine(-1,-1,-1,-1);
    experiment->fanRight()->setLine(-1,-1,-1,-1);
    experiment->updateGrid();

    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::Grid_Left;
    emit statusMessage(tr("Drag a line to define the left boundary of the fan"));
    repaint();
}

void ImageWidget::updateGridLines(int lines)
{
    experiment->setFanLines(lines);
    experiment->updateGrid();
    repaint();
}

int ImageWidget::nearestGridMark(QPoint pt)
{
    // http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=geometry1#line_point_distance
    // http://mathworld.wolfram.com/CrossProduct.html
    int minindex = -1;
    float mindistance = 999999999999.0f, d;
    float ABx, ABy, ACx, ACy, cross, mag;

    for(int i=0; i<experiment->grid()->length(); i++)
    {
	// AB = B-A  //  AB = pt2 - pt1
	// BC = C-B  //  BC = pt1 - pt
	ABx = experiment->grid()->at(i).p2().x() - experiment->grid()->at(i).p1().x();
	ABy = experiment->grid()->at(i).p2().y() - experiment->grid()->at(i).p1().y();

	// AC = C-A  //  CA = pt - pt1
	ACx = pt.x() - experiment->grid()->at(i).p2().x();
	ACy = pt.y() - experiment->grid()->at(i).p2().y();
	cross = ABx*ACy - ABy*ACx;
	mag = sqrt( ABx*ABx + ABy*ABy  );
	d = abs( cross / mag );
	if( d < nearnessThreshold &&  d < mindistance )
	{
	    minindex = i;
	    mindistance = d;
	}
    }
    return minindex;
}

void ImageWidget::updateDotView()
{
    if(dotViewImage!=0) { delete dotViewImage; }
    dotViewImage = image->dotView();
}

void ImageWidget::dragTransformedView(bool drag)
{
    if(drag)
    {
	originalOffset = QPoint(session->palatronSettingsToUse()->OverlayX, session->palatronSettingsToUse()->OverlayY);
	prevInputMode = inputMode;
	if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
	inputMode = ImageWidget::TransformationPreDrag;
	this->setCursor(QCursor(Qt::OpenHandCursor));
    }
    else
    {
	inputMode = prevInputMode;
	this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void ImageWidget::selectFace()
{
    prevInputMode = inputMode;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }
    inputMode = ImageWidget::SelectFace;
    repaint();
}

void ImageWidget::updateCompositeView()
{
    if( compositeView != 0 ) { delete compositeView; }
    if( session->images()->length() < 1 ) { return; }

    int i, j, w, h;
    QRgb *colorBits, *monoBits;
    QRgb tmp;
    int d;

    QImage img(session->images()->at(0)->filename()); // get the first image of the session
    h = img.height();
    w = img.width();

    compositeView = new QImage(w,h,QImage::Format_RGB32); // make a new image of this size

    compositeView->fill(0); // fill it with black

    monoBits = (QRgb*)compositeView->bits(); // and monoBits is the pointer to the new images' data

    for( i=0; i<session->images()->length(); i++ )
    {
	QImage img(session->images()->at(i)->filename()); // load the next image
	colorBits = (QRgb*)img.bits(); // these are its bits

	for(j=0; j<img.byteCount()/4; j++)
	{
	    tmp = *(colorBits+j);
	    d = (int)sqrt(  (qRed(session->dotColor().rgb()) - qRed(tmp))*(qRed(session->dotColor().rgb()) - qRed(tmp)) + (qGreen(session->dotColor().rgb()) - qGreen(tmp))*(qGreen(session->dotColor().rgb()) - qGreen(tmp)) + (qBlue(session->dotColor().rgb()) - qBlue(tmp))*(qBlue(session->dotColor().rgb()) - qBlue(tmp)) );
	    if( d < session->tolerance() || *(monoBits+j) == qRgba(255,255,255,255) )
		*(monoBits+j) = qRgba(255,255,255,255);
    	}
	emit statusMessage(tr("Creating composite... ") + QString::number(100.0 * (double)i/(double)session->images()->length()) + "%");
    }
    emit statusMessage(tr("Ready"));

    repaint();
}

void ImageWidget::drawThePalate(int subject, int session)
{
    prevDisplayMode = displayMode;
    displayMode = ImageWidget::PalateDrawing;
    if(prevDisplayMode==displayMode) { prevDisplayMode = ImageWidget::Untransformed; }

    prevInputMode = inputMode;
    inputMode = ImageWidget::DrawPalate;
    if(prevInputMode==inputMode) { prevInputMode = ImageWidget::Trace; }

    repaint();
    emit statusMessage(tr("Draw the palate"));
}

void ImageWidget::updateTraditionalTransformed()
{
    if( traditionalTransformed != 0 ) { delete traditionalTransformed; }

    if(!image->palatron()) { QMessageBox::critical(this,"PalatoglossatronQt Error","Palatron could not be run on this image because one or more of the dots was not found. Either the image is bad or you need to redefine the dot-tracking boxes (the Palatron boxes)."); }

    QImage tmp;
    QTransform transform;
    transform.scale(session->palatronSettingsToUse()->horizontal_distortion_correction,session->palatronSettingsToUse()->vertical_distortion_correction);
    tmp = imageimage->transformed(transform);

    transform.reset();
    transform.rotateRadians(-1 * image->angle());
    //    transform.rotateRadians(image->angle());
    traditionalTransformed = new QImage(tmp.transformed(transform));

    //    qDebug() << "offset()" << traditionalTransformed->offset();

    // faceImage can come from the scaled (but not rotated) tmp variable
    if( faceImage != 0 ) { delete faceImage; }
    faceImage = new QImage(tmp.copy(0,0,session->palatronSettingsToUse()->faceLocation,tmp.height()));
}

void ImageWidget::resetPalateImages(int subj,int sess)
{
    //    qDebug() << "reset start";
    int i;

    QImage tmp1,tmp2;
    QTransform transform;

    for(i=0; i<aPalateImages.count(); i++)
    {
	delete aPalateImages.takeFirst();
    }
    for(i=0; i<session->palateImages()->count(); i++)
    {
	//	qDebug() << "for" << i;

	session->palateImages()->at(i)->trackDots();

	if(session->palateImages()->at(i)->palatron())
	{
	    //	qDebug() << "resetPalateImages" << session->palateImages()->at(i)->xoffset() << session->palateImages()->at(i)->yoffset();

	    transform.reset();
	    tmp1.load(session->palateImages()->at(i)->filename());
	    transform.scale(session->palatronSettingsToUse()->horizontal_distortion_correction,session->palatronSettingsToUse()->vertical_distortion_correction);
	    tmp2 = tmp1.transformed(transform);
	    transform.reset();
	    transform.rotateRadians(-1 * session->palateImages()->at(i)->angle());

	    //	    qDebug() << "resetPalateImages" << session->palateImages()->at(i)->xoffset() << session->palateImages()->at(i)->yoffset();

	    aPalateImages << new QImage(tmp2.transformed(transform));
	}
	else
	{
	    aPalateImages << new QImage(1,1,QImage::Format_ARGB32);
	    aPalateImages.last()->setPixel(0,0,0xff000000);
	}
    }
}

void ImageWidget::autoTrace()
{
    if(imageimage == 0) { return; }

    int tracingAlgorithm = experimentarea->currentTracing();
    if(tracingAlgorithm == -1) { QMessageBox::critical(this,"PalatoglossatronQt Error","There is no available tracing algorithm. The automatic tracer is not available."); return; }

    if(this->inputMode == ImageWidget::Trace)
    {
	image->traces()->at(this->index)->points()->clear();
	image->traces()->at(this->index)->pointsTransformed()->clear();
	image->traces()->at(this->index)->points()->append(experimentarea->automaticTracers()->at(tracingAlgorithm)->trace(imageimage));
    }

    this->update();
}

void ImageWidget::refreshPalate()
{
    if( imageType == ImageWidget::Palate )
	this->update();
}

void ImageWidget::updateIfPluginDislay()
{
    if(displayMode == ImageWidget::Plugin)
	this->update();
}

QList<QPoint*>* ImageWidget::currentTrace() const
{
    if( image != 0 && image->traces()->count() > this->index )
	return image->traces()->at(this->index)->points();
    else
	return new QList<QPoint*>;
}

void ImageWidget::setInvertedImage(bool inverted)
{
    bDrawInvertedImage = inverted;
    this->update();
}
