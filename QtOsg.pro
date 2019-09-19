#-------------------------------------------------
#
# Project created by QtCreator 2019-08-12T11:41:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOsg
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        AdapterWidget.cpp \
        editwidget.cpp \
        main.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        ViewerQT.h \
        adapterwidget.h \
        editwidget.h \
        mainwindow.h

FORMS += \
        mainwindow.ui
UI_DIR=./UI

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../OSG/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../OSG/lib/ -losgd
else:unix: LIBS += -L$$PWD/../../../../../../../../OSG/lib/ -losg

INCLUDEPATH += $$PWD/../../../../../../../../OSG/include
DEPENDPATH += $$PWD/../../../../../../../../OSG/include

libpath +=$$PWD/../../../../../../../../OSG/lib

QT += opengl

LIBS +=-L$$libpath

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losg
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgd
else:unix: LIBS += -LC:/OSG/lib/ -losg

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgDB
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgDBd
else:unix: LIBS += -LC:/OSG/lib/ -losgDB

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgDB
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgDBd
else:unix: LIBS += -LC:/OSG/lib/ -losgDB

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgFX
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgFXd
else:unix: LIBS += -LC:/OSG/lib/ -losgFX

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgGA
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgGAd
else:unix: LIBS += -LC:/OSG/lib/ -losgGA

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgUtil
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgUtild
else:unix: LIBS += -LC:/OSG/lib/ -losgUtil

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgViewer
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgViewerd
else:unix: LIBS += -LC:/OSG/lib/ -losgViewer

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgQt5
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgQt5d
else:unix: LIBS += -LC:/OSG/lib/ -losgQt5

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -lOpenThreads
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -lOpenThreadsd
else:unix: LIBS += -LC:/OSG/lib/ -lOpenThreads

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgParticle
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgParticled
else:unix: LIBS += -LC:/OSG/lib/ -losgParticle

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgText
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgTextd
else:unix: LIBS += -LC:/OSG/lib/ -losgText

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgManipulator
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgManipulatord
else:unix: LIBS += -LC:/OSG/lib/ -losgManipulator

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgPresentation
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgPresentationd
else:unix: LIBS += -LC:/OSG/lib/ -losgPresentation

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgShadow
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgShadowd
else:unix: LIBS += -LC:/OSG/lib/ -losgShadow

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgSim
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgSimd
else:unix: LIBS += -LC:/OSG/lib/ -losgSim

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include

win32:CONFIG(release, debug|release): LIBS += -LC:/OSG/lib/ -losgTerrain
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/OSG/lib/ -losgTerraind
else:unix: LIBS += -LC:/OSG/lib/ -losgTerrain

INCLUDEPATH += C:/OSG/include
DEPENDPATH += C:/OSG/include
