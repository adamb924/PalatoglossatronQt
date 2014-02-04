#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDir>

#include "defaultsettings.h"
#include "interfaces.h"

class QMdiArea;
class QPushButton;
class QLineEdit;
class QStringListModel;
class Experiment;
class Projectoptions;
class QAction;
class QActionGroup;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int currentTracing();
    QList<TrackingInterface*>* automaticTracers();
    bool setTracer(QString name);

    QList<DisplayInterface*>* widgetDisplays();
    DisplayInterface* displayPlugin(int i);

protected:
    QAction *mNew, *mOpen, *mSave, *mSaveAs, *mClose, *mExit, *mExport, *mImportTabDelimited;
    QAction *mSubjects, *mDisplay, *mImages, *mAnnotations, *mPalatron;
    QMenu *fileMenu, *toolbarsMenu, *tracingMenu, *pluginSettingsMenu, *windowsMenu;
    QActionGroup *tracingActionGroup;

    void populateWindowsMenu();

private:
    QWidget *welcomeDialog;
    Projectoptions *optionsWidget;

    Experiment *experiment;

    void WelcomeView();

    void setupActions();
    void setupMenus();

    QDir pluginsDir;
    QStringList pluginFileNames;
    void loadPlugins();
    void loadPlugin(QObject *plugin);
    QList<TrackingInterface*> tracers;
    QList<DisplayInterface*> displays;

signals:
    void displayPluginSettingsUpdated();

public slots:
    // Mode Views
    void MainView();

    void CreateProjectView();


    void createNewProject();

    void openProject();
    void saveProject();
    void saveProjectAs();
    void exportData();
    void importTabDelimitedData();
    void closeProject();

private slots:
    void tracerChanged(QAction *action);
    void sendGridToTracers();
    void sendTraceToPlugin(int i, int j);
};

#endif // MAINWINDOW_H
