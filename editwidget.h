#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsScene>

class editwidget : public QWidget
{
    Q_OBJECT
public:
    explicit editwidget(QWidget *parent = nullptr);
    QPushButton texture;
    QPushButton apply;
    QGraphicsView review;
    QGraphicsScene *texture_scene;
    QString texturepath;
signals:
    void applytexture();

public slots:
private:

};

#endif // EDITWIDGET_H
