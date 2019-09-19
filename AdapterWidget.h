#ifndef	 AdapterWidget_H
#define  AdapterWidget_H

#include <osg/ArgumentParser>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <QString>
#include <QTimer>
#include <QtGui/QKeyEvent>
#include <QApplication>
#include <QtOpenGL/QGLWidget>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QMdiArea>
#include <QtGui>

#include <iostream>

using Qt::WindowFlags;

class AdapterWidget:public QGLWidget
{
public:
    AdapterWidget(QWidget *parent=0,const char* name=0,const QGLWidget * shareWidget=0,WindowFlags f=0);

    virtual ~AdapterWidget()
    {

    }

    osgViewer::GraphicsWindow* getGraphicsWindow()
    {
        return _gw.get();
    }

    const osgViewer::GraphicsWindow* getGraphicsWidow()const
    {
        return _gw.get();
    }
protected:
    void init();
    virtual void resizeGL(int width,int height);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);//
    virtual void mouseMoveEvent(QMouseEvent* event);

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;

};

#endif

