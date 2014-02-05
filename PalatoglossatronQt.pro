# -------------------------------------------------
# Project created by QtCreator 2010-02-19T13:37:03
# -------------------------------------------------
QT += widgets gui xml
TARGET = PalatoglossatronQt
TEMPLATE = app

# CONFIG += console
SOURCES += main.cpp \
    mainwindow.cpp \
    experiment.cpp \
    welcomewidget.cpp \
    projectoptions.cpp \
    listeditorwidget.cpp \
    experimentarea.cpp \
    subjectwidget.cpp \
    session.cpp \
    subject.cpp \
    image.cpp \
    treeitem.cpp \
    imagelistwidget.cpp \
    annotationwidget.cpp \
    imagewidget.cpp \
    defaultsettings.cpp \
    dataentrywidget.cpp \
    palatronwidget.cpp \
    point.cpp \
    trace.cpp \
    palateimagespecifier.cpp \
    displaysettingswidget.cpp \
    palatronsettings.cpp
HEADERS += mainwindow.h \
    experiment.h \
    trace.h \
    subject.h \
    session.h \
    image.h \
    welcomewidget.h \
    projectoptions.h \
    listeditorwidget.h \
    experimentarea.h \
    subjectwidget.h \
    treeitem.h \
    imagelistwidget.h \
    annotationwidget.h \
    imagewidget.h \
    dataentrywidget.h \
    palatronwidget.h \
    point.h \
    globals.h \
    defaultsettings.h \
    palateimagespecifier.h \
    displaysettingswidget.h \
    interfaces.h \
    SettingsAction.h \
    palatronsettings.h
FORMS += 
LIBS += -L./ \
    -llibexslt \
    -llibxslt \
    -llibxml2 \
    -liconv
