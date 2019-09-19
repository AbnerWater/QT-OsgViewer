#ifndef	 ViewerQT_H
#define  ViewerQT_H

#include "AdapterWidget.h"

using Qt::WindowFlags;
#include <iostream>

class ViewerQT : public osgViewer::Viewer, public AdapterWidget
{
public:
    ViewerQT(QWidget * parent=0,const char * name=0,const QGLWidget * shareWidget=0,WindowFlags f=0):AdapterWidget(parent ,name,shareWidget ,f)
    {
        getCamera()->setViewport(new osg::Viewport(0,0,width(),height()));
        getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width())/static_cast<double>(height()), 1.0f, 10000.0f);
        getCamera()->setGraphicsContext(getGraphicsWindow());

        setThreadingModel(osgViewer::Viewer::SingleThreaded);
        connect(&_timer,SIGNAL(timeout()),this,SLOT(updateGL()));//并且把它的timeout()连接到适当的槽。当这段时间过去了，它将会发射timeout()信号。

        _timer.start(10);//使用start()来开始

    }

    virtual void paintGL()
    {
        frame();
    }
protected:
    QTimer _timer;
};

#endif
