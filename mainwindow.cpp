#include "mainwindow.h"
#include "welcomewidget.h"
#include "projectoptions.h"
#include "experimentarea.h"
#include "listeditorwidget.h"

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QScrollArea>
#include <QtDebug>
#include <QLineEdit>
#include <QShortcut>
#include <QDockWidget>
#include <QStringListModel>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPluginLoader>
#include <QDir>
#include <QApplication>
#include <QActionGroup>
#include <QXmlStreamReader>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QStringList>
#include <QInputDialog>

#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/DOCBparser.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libexslt/exslt.h>

#include "experiment.h"
#include "defaultsettings.h"
#include "interfaces.h"
#include "dataentrywidget.h"
#include "SettingsAction.h"

MainWindow::MainWindow(QWidget *parent)
{
    experiment = 0;

    setupActions();
    setupMenus();

    this->setWindowTitle(tr("Palatoglossatron Qt"));

    loadPlugins();

    WelcomeView();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupActions()
{
    mNew = new QAction(tr("New project"),this);
    mNew->setShortcut(QKeySequence("Ctrl+N"));
    mOpen = new QAction(tr("Open project"),this);
    mOpen->setShortcut(QKeySequence("Ctrl+O"));
    mSave = new QAction(tr("Save project"),this);
    mSave->setShortcut(QKeySequence("Ctrl+S"));
    mSaveAs = new QAction(tr("Save project as..."),this);
    mSaveAs->setShortcut(QKeySequence("Ctrl+Shift+S"));
    mImportTabDelimited = new QAction(tr("Import PG tab-delimited..."),this);
    mImportTabDelimited->setShortcut(QKeySequence("Ctrl+I"));
    mExport = new QAction(tr("Export data..."),this);
    mExport->setShortcut(QKeySequence("Ctrl+E"));
    mClose = new QAction(tr("Close project"),this);
    mClose->setShortcut(QKeySequence("Ctrl+F4"));
    mExit = new QAction(tr("Exit program"),this);
    mExit->setShortcut(QKeySequence("Ctrl+Q"));

    connect(mNew,SIGNAL(triggered()),this,SLOT(CreateProjectView()));
    connect(mOpen,SIGNAL(triggered()),this,SLOT(openProject()));
    connect(mSave,SIGNAL(triggered()),this,SLOT(saveProject()));
    connect(mSaveAs,SIGNAL(triggered()),this,SLOT(saveProjectAs()));
    connect(mExport,SIGNAL(triggered()),this,SLOT(exportData()));
    connect(mClose,SIGNAL(triggered()),this,SLOT(closeProject()));
    connect(mExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(mImportTabDelimited,SIGNAL(triggered()),this,SLOT(importTabDelimitedData()));

    mSubjects = new QAction(tr("Subjects and Sessions"),this);
    mSubjects->setCheckable(true); mSubjects->setChecked(true);
    mDisplay = new QAction(tr("Display Settings"),this);
    mDisplay->setCheckable(true); mDisplay->setChecked(true);
    mImages = new QAction(tr("Images"),this);
    mImages->setCheckable(true); mImages->setChecked(true);
    mAnnotations = new QAction(tr("Annotations"),this);
    mAnnotations->setCheckable(true); mAnnotations->setChecked(true);
    mPalatron = new QAction(tr("Palatron"),this);
    mPalatron->setCheckable(true); mPalatron->setChecked(true);
}

void MainWindow::setupMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(mNew);
    fileMenu->addAction(mOpen);
    fileMenu->addAction(mSave);
    fileMenu->addAction(mSaveAs);
    fileMenu->addAction(mClose);
    fileMenu->addSeparator();
    fileMenu->addAction(mImportTabDelimited);
    fileMenu->addAction(mExport);
    fileMenu->addSeparator();
    fileMenu->addAction(mExit);

    toolbarsMenu = menuBar()->addMenu(tr("&Toolbars"));
    toolbarsMenu->setEnabled(false);
    toolbarsMenu->addAction(mSubjects);
    toolbarsMenu->addAction(mDisplay);
    toolbarsMenu->addAction(mImages);
    toolbarsMenu->addAction(mAnnotations);
    toolbarsMenu->addAction(mPalatron);

    tracingMenu = menuBar()->addMenu(tr("T&racing"));
    tracingMenu->setEnabled(false);
    tracingActionGroup = new QActionGroup(this);
    connect(tracingActionGroup,SIGNAL(triggered(QAction*)),this,SLOT(tracerChanged(QAction*)));

    pluginSettingsMenu = menuBar()->addMenu(tr("&Plugin Settings"));

    windowsMenu = menuBar()->addMenu(tr("&Windows"));
}

void MainWindow::populateWindowsMenu()
{
    windowsMenu->clear();

    ExperimentArea *area = qobject_cast<ExperimentArea*>(centralWidget());
    if( area == 0 )
    {
	windowsMenu->setEnabled(false);
	return;
    }
    for(int i=0; i< area->subWindowList().count(); i++)
    {
	QAction *action = new QAction(area->subWindowList().at(i)->windowTitle(), windowsMenu);
	windowsMenu->addAction(action);
    }
}

void MainWindow::WelcomeView()
{
    toolbarsMenu->setEnabled(false);
    WelcomeWidget *welcomeDialog = new WelcomeWidget(this);
    connect(welcomeDialog->create,SIGNAL(clicked()),this,SLOT(CreateProjectView()));
    connect(welcomeDialog->open,SIGNAL(clicked()),this,SLOT(openProject()));
    connect(welcomeDialog->exit,SIGNAL(clicked()),this,SLOT(close()));
    setCentralWidget(welcomeDialog); // crashes here
    this->setWindowTitle(tr("Palatoglossatron Qt"));
}

void MainWindow::CreateProjectView()
{
    toolbarsMenu->setEnabled(false);

    optionsWidget = new Projectoptions();
    connect(optionsWidget->createExperiment,SIGNAL(clicked()),this,SLOT(createNewProject()));

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(optionsWidget);
    setCentralWidget(scrollArea);

    this->setWindowTitle(tr("Palatoglossatron Qt"));
}

void MainWindow::MainView()
{
    if(centralWidget() != 0)
    {
	disconnect(centralWidget(), 0, 0, 0);
	delete centralWidget();
    }

    ExperimentArea *area = new ExperimentArea(this,experiment);

    connect(mSubjects,SIGNAL(triggered(bool)),area,SLOT(setSubjectsDockVisible(bool)));
    connect(mDisplay,SIGNAL(triggered(bool)),area,SLOT(setDisplayDockVisible(bool)));
    connect(mImages,SIGNAL(triggered(bool)),area,SLOT(setImagesDockVisible(bool)));
    connect(mAnnotations,SIGNAL(triggered(bool)),area,SLOT(setAnnotationsDockVisible(bool)));
    connect(mPalatron,SIGNAL(triggered(bool)),area,SLOT(setPalatronDockVisible(bool)));

    connect(this,SIGNAL(displayPluginSettingsUpdated()),area,SLOT(displayPluginSettingsUpdated()));

    connect(area,SIGNAL(sendGridToTracers()),this,SLOT(sendGridToTracers()));

    this->setWindowTitle(experiment->name());
    setCentralWidget(area);

    toolbarsMenu->setEnabled(true);
    tracingMenu->setEnabled(true);

    for(int i=0; i< displays.count(); i++)
    {
	area->addDisplayPlugin( displays.at(i)->name() );
    }
}

void MainWindow::createNewProject()
{
    if(experiment != 0)
    {
	delete experiment; experiment=0;
    }

    experiment = new Experiment;
    experiment->setName(optionsWidget->name->text());
    experiment->setDescription(optionsWidget->description->text());
    experiment->setTraceInterpretations(optionsWidget->traceWidget->stringsList());
    experiment->setPointInterpretations(optionsWidget->pointWidget->stringsList());
    experiment->setSubjectDataInterpretations(optionsWidget->subjectWidget->stringsList());
    experiment->setSessionDataInterpretations(optionsWidget->sessionWidget->stringsList());

    MainView();
}

void MainWindow::openProject()
{
    if(experiment != 0)
    {
	delete experiment; experiment=0;
    }

    experiment = new Experiment;

    QString fileName;
    fileName= QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Project Files (*.xml)"));
    if(!fileName.isNull())
    {
	if( experiment->readFromFile(fileName) )
	{
	    // need to set the tracer in this context
	    if(experiment->tracer().length()>0)
	    {
		setTracer(experiment->tracer());
	    }
	    else
	    {
		experiment->setTracer(tracingActionGroup->checkedAction()->text());
	    }

	    // include a call to set the settings here
	    sendGridToTracers();

	    for(int i=0; i< tracers.length(); i++)
	    {
		if( experiment->hasPluginSettings(tracers.at(i)->name()) ) // setting already exist, so send them to the plugin
		{
		    tracers.at(i)->receiveXMLSettings(experiment->pluginSettings(tracers.at(i)->name()));
		}
		else // no settings exist, so send the default settings to the experiment
		{
		    experiment->setPluginSettings(tracers.at(i)->name(),tracers.at(i)->settingsToXML());
		}
	    }

	    MainView();
	}
	else
	{
	    qDebug() << "Error reading project file.";
	    QMessageBox::information(this,"Error reading file","There was an error reading the file. There may be more useful information in the debug output.");
	    delete experiment;
	}
    }
}

void MainWindow::sendGridToTracers()
{
    for(int i=0; i<tracers.count(); i++)
    {
	if( tracers.at(i)->needsGrid() )
	{
	    tracers.at(i)->setGrid( experiment->grid() );
	}
    }
}

void MainWindow::saveProject()
{
    if(experiment == 0) { return; }

    if(experiment->currentFilename.length() > 0)
	{
	    for(int i=0; i< tracers.length(); i++)
	    {
		experiment->setPluginSettings(tracers.at(i)->name(),tracers.at(i)->settingsToXML());
	    }
	    experiment->serialize(experiment->currentFilename);
	}
	else
	{
	    saveProjectAs();
	}
}

void MainWindow::saveProjectAs()
{
    if(experiment != 0)
    {
	QString fileName;
	fileName= QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("Project Files (*.xml)"));
	if(!fileName.isNull())
	{
	    for(int i=0; i< tracers.length(); i++)
	    {
		experiment->setPluginSettings(tracers.at(i)->name(),tracers.at(i)->settingsToXML());
	    }
	    experiment->serialize(fileName);
	    experiment->currentFilename = fileName;
	}
    }
}

void MainWindow::closeProject()
{
    if(experiment != 0)
	delete experiment; experiment=0;
    WelcomeView();
//    qDebug() << "after WelcomeView";
}

void MainWindow::loadPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances())
	loadPlugin(plugin);

    pluginsDir = QDir(qApp->applicationDirPath());

#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
	pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
	pluginsDir.cdUp();
	pluginsDir.cdUp();
	pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");

//    qDebug() << pluginsDir.absolutePath();

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
//	qDebug() << pluginsDir.absoluteFilePath(fileName);
	QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
	QObject *plugin = loader.instance();
	if (plugin) {
	    loadPlugin(plugin);
	    pluginFileNames += fileName;
	}
    }
}

void MainWindow::loadPlugin(QObject *plugin)
{
    TrackingInterface *tracker = qobject_cast<TrackingInterface*>(plugin);
    if (tracker)
    {
	if( tracker->initialized() )
	{
	    tracers << tracker;
	    QAction *newAction = new QAction(tracker->name(),this);
	    newAction->setCheckable(true);
	    tracingMenu->addAction(newAction);
	    tracingActionGroup->addAction(newAction);

	    // for the plugin settings menu
	    QMenu* tmpMenu = pluginSettingsMenu->addMenu(tracker->name());

	    SettingsAction *tmp = new SettingsAction(tr("Settings"),tracker,this);
	    tmpMenu->addAction( tmp );
	    connect(tmp,SIGNAL(triggered()),tmp,SLOT(mytrigger()) );

	    QMenu* tmpMenu2 = tmpMenu->addMenu(tr("Trace settings"));
	    QStringList traceSettingNames = tracker->settingsTraceNames();
	    for(int i=0; i<traceSettingNames.count(); i++)
	    {
		DoubleIndexAction *tmpDS = new DoubleIndexAction(traceSettingNames.at(i), tracers.count()-1, i ,this);
		tmpMenu2->addAction( tmpDS );
		connect(tmpDS,SIGNAL(triggered()),tmpDS,SLOT(mytrigger()) );
		connect(tmpDS, SIGNAL(activated(int,int)), this, SLOT(sendTraceToPlugin(int,int)) );
	    }
	}
	else
	{
	    QMessageBox::critical(this,"PalatoglossatronQt Error","The plugin \""+tracker->name()+"\" did not initialize properly. If you wish to stop seeing this message you can delete the appropriate file from the plugin directory.");
	}
    }

    if(!pluginSettingsMenu->isEmpty())
    {
	pluginSettingsMenu->addSeparator();
    }

    DisplayInterface *display = qobject_cast<DisplayInterface*>(plugin);
    if(display)
    {
	displays << display;

	// for the plugin settings menu
	SettingsAction *tmp = new SettingsAction(display->name(),display,this);
	pluginSettingsMenu->addAction( tmp );
	connect(tmp,SIGNAL(triggered()),tmp,SLOT(mytrigger()) );
	connect(tmp,SIGNAL(triggered()),this,SIGNAL(displayPluginSettingsUpdated()));
    }

    if (!tracingActionGroup->actions().isEmpty())
	tracingActionGroup->actions().first()->trigger();
}

int MainWindow::currentTracing()
{
    QString label = tracingActionGroup->checkedAction()->text();
//    qDebug() << label;
    for(int i=0; i<tracers.length(); i++)
    {
	if(tracers.at(i)->name()==label)
	{
	    return i;
	}
    }
    return -1;
}

QList<TrackingInterface*>* MainWindow::automaticTracers()
{
    return &tracers;
}

QList<DisplayInterface*>* MainWindow::widgetDisplays()
{
    return &displays;
}


void MainWindow::tracerChanged(QAction *action)
{
    if(experiment != 0)
    {
	experiment->setTracer(action->text());
    }
}

bool MainWindow::setTracer(QString name)
{
    for(int i=0; i<tracers.length(); i++)
    {
	if(tracers.at(i)->name()==name)
	{
	    tracingActionGroup->actions().at(i)->setChecked(true);
	    return true;
	}
    }
    QMessageBox::critical(this,"PalatoglossatronQt Error","The tracing algorithm \""+name+"\" could not be found. Another tracing algorithm will be used instead.");
    return false;
}

DisplayInterface* MainWindow::displayPlugin(int i)
{
    if(i>=0 && i < displays.count())
    {
	return displays.at(i);
    }
    else
    {
	return NULL;
    }
}

void MainWindow::exportData()
{
    if(experiment == 0) { return; }

    QString xslFilename;
    xslFilename= QFileDialog::getOpenFileName(this, tr("XSL File"), "", tr("XSLT File (*.xsl)"));
    if(xslFilename.isNull()) { return; }

    QString destinationFilename;
    destinationFilename= QFileDialog::getSaveFileName(this, tr("Any file"));
    if(destinationFilename.isNull()) { return; }

    /* Find the parameters that the XSL file is requesting */
    QStringList parameters, values;
    QFile file(xslFilename);
    if(! file.open(QFile::ReadOnly | QFile::Text) ) { QMessageBox::critical(this,tr("PalatoglossatronQt Error"),tr("Could not open the .xsl file.")); return; }
    QXmlStreamReader xml(&file);

    while (!xml.atEnd()) {
	if(xml.readNext() == QXmlStreamReader::StartElement)
	{
	    if( xml.name().toString() == "param" && xml.namespaceUri() == "http://www.w3.org/1999/XSL/Transform" )
	    {
		parameters << xml.attributes().value("name").toString();
	    }
	    if( xml.name().toString() == "template" && xml.namespaceUri() == "http://www.w3.org/1999/XSL/Transform" ) // we've moved past the initial parameters
	    {
		break;
	    }
	}
    }
    file.close();

    if(parameters.length() > 8)
    {
	QMessageBox::critical(this,tr("PalatoglossatronQt Error"),tr("The .xsl file is requesting more than 8 parameters, which is too many."));
	return;
    }

    const char *params[16 + 1];
    int nbparams = 0;

    if(parameters.length() > 0)
    {
	DataEntryWidget *form = new DataEntryWidget(&parameters, &values, tr("The XSL file has requested the following parameters.\nIt may be possible to leave some or all blank."),this);
	if( form->exec() == QDialog::Accepted)
	{
	    for(int i=0; i<parameters.length(); i++)
	    {
		if(values.at(i).length() > 0)
		{
		    values[i] = "\"" + values.at(i) + "\"";
            QByteArray *p = new QByteArray(parameters.at(i).toLatin1());
		    params[nbparams++] = p->data();
            QByteArray *v = new QByteArray(values.at(i).toLatin1());
		    params[nbparams++] = v->data();
		}
	    }
	}
    }

    xsltStylesheetPtr cur = NULL;
    xmlDocPtr doc, res;
    params[nbparams] = NULL;

    exsltRegisterAll();

    xmlSubstituteEntitiesDefault(1);
    xmlLoadExtDtdDefaultValue = 1;

    QByteArray ba = xslFilename.toLatin1();

    cur = xsltParseStylesheetFile( (const xmlChar*)ba.data() );
    doc = xmlParseFile( (const char*) experiment->currentFilename.toLatin1() );
    res = xsltApplyStylesheet(cur, doc, (const char**)params);

    FILE *fid = fopen(destinationFilename.toUtf8(),"w");
    xsltSaveResultToFile(fid, res, cur);
    fclose(fid);

    xsltFreeStylesheet(cur);
    xmlFreeDoc(res);
    xmlFreeDoc(doc);

    xsltCleanupGlobals();
    xmlCleanupParser();
}

void MainWindow::sendTraceToPlugin(int i, int j)
{
    ExperimentArea* area = qobject_cast<ExperimentArea*>( this->centralWidget() );
    if( area == 0 || !(i < tracers.count()) ) { return; }

    if( ! tracers.at(i)->setSettingTrace(j, area->currentTrace()) )
    {
	QMessageBox::critical(this,tr("Error"),tr("There's been some kind of error in setting that trace. The debug log might have more information."));
    }
    else
    {
	QMessageBox::information(this,tr("Success"),tr("The trace has been set."));
    }
}

void MainWindow::importTabDelimitedData()
{
    if(experiment == 0) { return; }

    QString fileName;
    fileName= QFileDialog::getOpenFileName(this, tr("Open tab-delimited file"), "", tr("Text files (*.txt)"));
    if(!fileName.isNull())
    {
	bool ok;
	QString subject = QInputDialog::getText(0, tr("Enter the name of the subject"),
					     tr("Enter the name of the subject:"), QLineEdit::Normal,
					     "", &ok);

	if (ok && !subject.isEmpty())
	{
	    QString session = QInputDialog::getText(this, tr("Enter a name for the session"),
						 tr("Enter a name for the session:"), QLineEdit::Normal,
						 "", &ok);

	    if (ok && !session.isEmpty())
		experiment->addSessionFromTabDelimitedFile(fileName,subject,session);

	    ExperimentArea* area = qobject_cast<ExperimentArea*>( this->centralWidget() );
	    area->RefreshSubjectsDock();
	}
    }
}
