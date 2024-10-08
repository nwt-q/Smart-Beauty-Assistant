 #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);

    //设置窗口图标
    this->setWindowIcon(QIcon(":/sound/other/btn1.png"));
    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //背景透明
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口顶层
    this->setWindowFlags(this->windowFlags() |Qt::Tool);
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
    //鼠标右键 与 点击
    if (event->type() == QEvent::MouseMove) {
        qDebug() << "Mouse Move Event:" << event->pos();
        //移动窗口
        /*
         *  this->current_pos = QPoint(e->globalPos()-m_pos);
         *  this->move(e->globalPos()-this->m_pos);
        */
        pix.load(":/sound/img/shime111.png");
        this->current_pos = QPoint(event->globalPosition().toPoint() - m_pos);
        this->move(event->globalPosition().toPoint()-this->m_pos);
    }

}

/*
    功能： 鼠标按下根据点击次数更换动作
    参数：QMouseEvent * event
    返回值：void
*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //鼠标按下记录分量
    m_pos = event->globalPos()-this->pos();
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
    功能： 绘画显示图像(无背景) => 需要将窗口隐藏
    参数：void
    返回值：void
*/
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    pix.load(":/sound/img/shime111.png");
    painter.drawPixmap(0,0,pix);
}
