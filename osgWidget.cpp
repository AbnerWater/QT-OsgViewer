#include "osgWidget.h"
#include <QHBoxLayout>
#include <osg/LineWidth>
osgWidget::osgWidget(osg::Node* model, osgViewer::ViewerBase::ThreadingModel threadingModel)
    :QWidget()
{
    setThreadingModel(threadingModel);  //qt5 must single thread.else be crash
    setKeyEventSetsDone(0);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QWidget *mainWidget = getWidgetFromGraphicWinQt(createGraphicWindow(20, 20 ,640, 480), model);
    mainLayout->addWidget(mainWidget);
    modelnode=model;
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.start(10);  //刷新(重绘)频率
}

osgWidget::~osgWidget()
{

}

osg::Node *osgWidget::makeCoordinate(QString path)
{
    //创建保存几何信息的对象
    osg::ref_ptr<osg::Node> geom = osgDB::readNodeFile(path.toStdString());
    return geom;
}

osgQt::GraphicsWindowQt* osgWidget::createGraphicWindow(int x, int y, int width, int height, const QString strName, bool bWindosDecoration)
{
    osg::DisplaySettings *ds = osg::DisplaySettings::instance().get();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    traits->x = x;
    traits->y = y;
    traits->width = width;
    traits->height = height;
    traits->doubleBuffer = true;
    traits->alpha = ds->getMinimumNumAccumAlphaBits();
    traits->stencil = ds->getMinimumNumStencilBits();
    traits->sampleBuffers = ds->getMultiSamples();
    traits->samples = ds->getNumMultiSamples();
    return new osgQt::GraphicsWindowQt(traits.get());
}

QWidget *osgWidget::getWidgetFromGraphicWinQt(osgQt::GraphicsWindowQt *winQt, osg::Node *scene)
{
    osgViewer::View *view = new osgViewer::View;
    addView(view);


    osg::Camera *camera = view->getCamera();
    camera->setGraphicsContext(winQt);

    const osg::GraphicsContext::Traits *pTrait = winQt->getTraits();
    camera->setClearColor(osg::Vec4(0.2f, 0.2f, 0.6f, 1.0f));
    camera->setViewport(new osg::Viewport(0, 0, pTrait->width, pTrait->height));
    camera->setProjectionMatrixAsPerspective(30, static_cast<double>(pTrait->width) / static_cast<double>(pTrait->height), 1.0, 10000);

    view->setSceneData(scene);
    view->addEventHandler(new osgViewer::StatsHandler);
    view->setCameraManipulator(new osgGA::TrackballManipulator);
    return winQt->getGLWidget();
}

void osgWidget::paintEvent(QPaintEvent *e)
{
    frame();
}

