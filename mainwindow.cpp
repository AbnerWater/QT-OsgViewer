#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editwidget.h"
#include <QColorDialog>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/PolygonMode>
#include <osg/ShapeDrawable>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgFX/Scribe>
#include <osg/TexGen>

#include "qdebug.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    editwidget1=new editwidget();
    editwidget1->setWindowTitle("添加纹理");
    this->setWindowTitle("刘冰青的暑期作业");

    viewer =new ViewerQT(this);
    setCentralWidget(viewer);

    //菜单栏初始化
    about=new QAction(QStringLiteral("about"),this);
    menuBar()->addAction(about);
    status=new QLabel();
    statusBar()->addWidget(status);
    status->setText("ready");
    ui->actionsave->setEnabled(false);
    ui->actionclose->setEnabled(false);
    ui->actionnormal->setEnabled(false);

    //关于对话框点击事件
    connect(about,&QAction::triggered,
            [=]()
    {
        QMessageBox::about(this,"about","基于OSG与QT的三维模型浏览器\n刘冰青AbnerWater\n 2019.8.18");
    });

    //打开文件
    connect(ui->actionopen,&QAction::triggered,
            [=]()
    {
        if(path=="null")
        {
            status->setText("reading file");
            path=QFileDialog::getOpenFileName(this,"open","../","3D(*.stl;*.obj);;ALL(*.*)");
            qDebug()<<path;
            model=osgDB::readRefNodeFile(path.toStdString())->asGroup()->getChild(0)->asGeode();
            model->setCullingActive(true);
            //读取配置文件并加载
            if(QFile::exists(path+"ini"))
            {
                //读取配置文件
                status->setText("reading config file");
                config_file=new QSettings(path+"ini",QSettings::IniFormat);
                config_file->beginGroup("color");
                r=config_file->value("r").toFloat();
                g=config_file->value("g").toFloat();
                b=config_file->value("b").toFloat();
                a=config_file->value("a").toFloat();
                editwidget1->texturepath=config_file->value("texturepath").toString();
                config_file->endGroup();
                //加载配置文件
                osg::ref_ptr<osg::Material> material = new osg::Material();
                osg::ref_ptr<osg::ShapeDrawable> shap=new osg::ShapeDrawable();
                shap->setColor(osg::Vec4(r,g,b,a));
                model->addDrawable(shap);
                material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置光照
                material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置融合
                material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置镜面反射
                material->setShininess(osg::Material::FRONT_AND_BACK, 20.0);
                material->setColorMode(osg::Material::DIFFUSE);
                osg::ref_ptr<osg::StateSet> setting = model->getOrCreateStateSet();
                setting->setAttributeAndModes(material.get(), osg::StateAttribute::ON);
                setting->setMode(GL_BLEND, osg::StateAttribute::ON);//设置透明度
                setting->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
                osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D();
                osg::ref_ptr<osg::Image> image=osgDB::readImageFile(editwidget1->texturepath.toStdString());
                texture->setImage(image.get());
                setting->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
            }
            else
            {
                QMessageBox::warning(this,"warning","Can`t Find The Config File");
            }
            viewer->setSceneData(model.get());
            viewer->setCameraManipulator(new osgGA::TrackballManipulator);
            viewer->addEventHandler(new osgViewer::StatsHandler);
            {
               //自定义操作按键
               osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
               keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
               keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
               keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
               keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );
               viewer->setCameraManipulator( keyswitchManipulator.get() );
            }
            viewer->show();
            status->setText("ready");
            ui->actionsave->setEnabled(true);
            ui->actionclose->setEnabled(true);
            ui->actionnormal->setEnabled(false);
            ui->actionpoly->setEnabled(true);
        }
        else
        {
            int ret=QMessageBox::question(this,"save","Do You Want to Save the Current File?");
            switch (ret) {
            case QMessageBox::Yes:
            {
                status->setText("saving file");
                osgDB::writeNodeFile(*(model.get()),path.toStdString());
                config_file=new QSettings(path+"ini",QSettings::IniFormat);
                config_file->beginGroup("color");
                config_file->setValue("r",r);
                config_file->setValue("g",g);
                config_file->setValue("b",b);
                config_file->setValue("a",a);
                config_file->setValue("texturepath",editwidget1->texturepath);
                config_file->endGroup();
                path ="null";
                status->setText("ready");
            }break;
            case QMessageBox::No:
            {
                path ="null";
                viewer->close();
                ui->actionsave->setEnabled(false);
                ui->actionclose->setEnabled(false);
            }break;
            default:break;
            }
        }
    });

    //保存文件
    connect(ui->actionsave,&QAction::triggered,
            [=]()
    {
        status->setText("saving file");
        osgDB::writeNodeFile(*(model.get()),path.toStdString());
        config_file=new QSettings(path+"ini",QSettings::IniFormat);
        config_file->beginGroup("color");
        config_file->setValue("r",r);
        config_file->setValue("g",g);
        config_file->setValue("b",b);
        config_file->setValue("a",a);
        config_file->setValue("texturepath",editwidget1->texturepath);
        config_file->endGroup();
        path ="null";
        status->setText("ready");
    });

    //关闭当前模型
    connect(ui->actionclose,&QAction::triggered,
            [=]()
    {
        if(path=="null")
        {
            viewer->close();
            ui->actionsave->setEnabled(false);
            ui->actionclose->setEnabled(false);
        }
        else
        {
            int ret=QMessageBox::question(this,"save","Do You Want to Save the Current File?");
            switch (ret) {
            case QMessageBox::Yes:
            {
                status->setText("saving file");
                osgDB::writeNodeFile(*(model.get()),path.toStdString());
                config_file=new QSettings(path+"ini",QSettings::IniFormat);
                config_file->beginGroup("color");
                config_file->setValue("r",r);
                config_file->setValue("g",g);
                config_file->setValue("b",b);
                config_file->setValue("a",a);
                config_file->setValue("texturepath",editwidget1->texturepath);
                config_file->endGroup();
                path ="null";
                status->setText("ready");
            }break;
            case QMessageBox::No:
            {
                path ="null";
                viewer->close();
                ui->actionsave->setEnabled(false);
                ui->actionclose->setEnabled(false);
            }break;
            default:break;
            }
        }
    });

    //编辑颜色对话框
    connect(ui->actioncolor,&QAction::triggered,
            [=]()
    {
        rgb = QColorDialog::getColor(Qt::white, nullptr,"颜色选取",QColorDialog::ShowAlphaChannel);
        qDebug()<<rgb.alpha();
        qDebug()<<rgb.red();
        qDebug()<<rgb.green();
        qDebug()<<rgb.blue();
        //对节点进行颜色处理
        r=rgb.red()/255.f;g=rgb.green()/255.f;b=rgb.blue()/255.f;a=rgb.alpha()/255.f;
        osg::ref_ptr<osg::Material> material = new osg::Material();
        osg::ref_ptr<osg::ShapeDrawable> shap=new osg::ShapeDrawable();
        shap->setColor(osg::Vec4(r,g,b,a));
        model->addDrawable(shap);
        material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置光照
        material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置融合
        material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(r,g,b,a));//设置镜面反射
        material->setShininess(osg::Material::FRONT_AND_BACK, 20.0);
        material->setColorMode(osg::Material::DIFFUSE);
        osg::ref_ptr<osg::StateSet> setting = model->getOrCreateStateSet();
        setting->setAttributeAndModes(material.get(), osg::StateAttribute::ON);
        setting->setMode(GL_BLEND, osg::StateAttribute::ON);//设置透明度
        setting->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
//      ---------------------
//      版权声明：本文为CSDN博主「wb175208」的原创文章，遵循CC 4.0 by-sa版权协议，转载请附上原文出处链接及本声明。
//      原文链接：https://blog.csdn.net/wb175208/article/details/80512191
        viewer->setSceneData(model.get());
    });

    //选择纹理
    connect(ui->actiontexture,&QAction::triggered,
            [=]()
    {
        editwidget1->show();
    });
    connect(editwidget1,&editwidget::applytexture,
            [=]()
    {
        osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D();
        osg::ref_ptr<osg::Image> image=osgDB::readImageFile(editwidget1->texturepath.toStdString());
        texture->setImage(image.get());
        osg::ref_ptr<osg::StateSet> state=model->getOrCreateStateSet();
        state->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
        viewer->setSceneData(model.get());
//      版权声明：本文为博主原创文章，遵循 CC 4.0 by-sa 版权协议，转载请附上原文出处链接和本声明。
//      本文链接：https://blog.csdn.net/wb175208/article/details/80512191
    });
    //切换显示模式
    connect(ui->actionpoly,&QAction::triggered,
            [=]()
    {
        osg::ref_ptr<osgFX::Scribe> sc=new osgFX::Scribe();
        osg::ref_ptr<osg::Group> root=new osg::Group();
        sc->addChild(model.get());
        root->addChild(sc.get());
        viewer->setSceneData(root.get());
        ui->actionnormal->setEnabled(true);
        ui->actionpoly->setEnabled(false);
    });
    connect(ui->actionnormal,&QAction::triggered,
            [=]()
    {
        viewer->setSceneData(model.get());
        ui->actionnormal->setEnabled(false);
        ui->actionpoly->setEnabled(true);
    });
    resize(1000,1000);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(path=="null")
    {
        event->accept();
    }
    else
    {
        int ret=QMessageBox::question(this,"save","Do You Want to Save the Current File?");
        switch (ret) {
        case QMessageBox::Yes:
        {
            status->setText("saving file");
            osgDB::writeNodeFile(*(model.get()),path.toStdString());
            config_file=new QSettings(path+"ini",QSettings::IniFormat);
            config_file->beginGroup("color");
            config_file->setValue("r",r);
            config_file->setValue("g",g);
            config_file->setValue("b",b);
            config_file->setValue("a",a);
            config_file->setValue("texturepath",editwidget1->texturepath);
            config_file->endGroup();
            path ="null";
            status->setText("ready");
            event->accept();
        }break;
        case QMessageBox::No:
        {
            event->accept();
        }break;
        default:break;
        }
    }
}
