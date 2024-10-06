#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
    功能： 鼠标移动
    参数：void
    返回值：void
*/
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

/*
    功能： 鼠标移动
    参数：void
    返回值：void
*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

/*
    功能： 鼠标移动
    参数：void
    返回值：void
*/
void MainWindow::enterEvent(QEvent *event)
{

}

/*
    功能： 动画显示
    参数：void
    返回值：void
*/
void MainWindow::showMovie()
{

}

/*
    功能： 动画显示
    参数：void
    返回值：void
*/
void MainWindow::showMovie1()
{

}

/*
    功能： 动画显示
    参数：void
    返回值：void
*/
void MainWindow::showMovie2()
{

}

/*
    功能： 动画显示
    参数：void
    返回值：void
*/
void MainWindow::showMovie3()
{

}

/*
    功能： 动画显示
    参数：void
    返回值：void
*/
void MainWindow::showMovie3Move()
{

}

/*
    功能： 绘画
    参数：void
    返回值：void
*/
void MainWindow::paintEvent(QPaintEvent *)
{

}
