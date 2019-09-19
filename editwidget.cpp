#include "editwidget.h"
#include<QFileDialog>
#include "qdebug.h"
#include<QPixmap>

editwidget::editwidget(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(500,500,600,400);
    texture.setText("添加纹理");
    texture.setGeometry(450,100,100,50);
    texture.setParent(this);
    texture.show();
    apply.setText("应用");
    apply.setGeometry(450,250,100,50);
    apply.setParent(this);
    apply.show();
    review.setGeometry(0,0,400,400);
    review.setParent(this);
    texture_scene=new QGraphicsScene(this);

    //预览纹理图片
    connect(&texture,&QPushButton::released,
            [=]()
    {
        texturepath=QFileDialog::getOpenFileName(this,"open","../","TEXTURE(*.jpg;*.png);;ALL(*.*)");
        qDebug()<<texturepath;
        texture_scene->addPixmap(QPixmap(texturepath));
        review.setScene(texture_scene);
        review.show();
    });

    //点击应用纹理
    connect(&apply,&QPushButton::released,
            [=]()
    {
        emit applytexture();
        review.close();
        close();
    });
    this->setFixedSize(600,400);
}
