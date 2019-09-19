#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"editwidget.h"
#include "ViewerQT.h"
#include<QColorDialog>
#include<QColor>
#include <QMessageBox>
#include <QSettings>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAction *about;
    editwidget *editwidget1;
    QColor rgb;
    float r,g,b,a;
    QString path="null";
    osg::ref_ptr<osg::Geode> model;
    ViewerQT *viewer;
    QSettings *config_file;
    QLabel *status;
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
