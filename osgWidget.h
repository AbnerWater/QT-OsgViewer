#ifndef OSGWIDGET_H
#define OSGWIDGET_H

#include <QWidget>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osgQt/GraphicsWindowQt>
#include <QTimer>
class osgWidget : public QWidget, public osgViewer::CompositeViewer
{
    Q_OBJECT

public:
    explicit osgWidget(osg::Node* model,osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::SingleThreaded);
    ~osgWidget();

public:
    osg::Node* makeCoordinate(QString path);
    osgQt::GraphicsWindowQt* createGraphicWindow(int x, int y, int width, int height,
                                                const QString strName = QString(""), bool bWindosDecoration = false);//create graphic window
    QWidget* getWidgetFromGraphicWinQt(osgQt::GraphicsWindowQt *winQt, osg::Node *scene);
    osg::Node* modelnode;

protected:
    virtual void paintEvent(QPaintEvent *e);

protected:
    QTimer m_timer;
};

#endif // OSGWIDGET_H
