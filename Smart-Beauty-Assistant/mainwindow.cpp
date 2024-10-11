 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口图标
    this->setWindowIcon(QIcon(":/sound/other/btn1.png"));
    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    //背景透明
    //this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // 将窗口固定大小
    QBitmap bmp(this->size());//设置圆角边框
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);


    //初始化定时器
    timer = new QTimer(this);
    //加载初始动作
    loadRoleActRes();

    //创建信号与槽
    connect(timer, &QTimer::timeout,[this](){
        static int index = 0; //记录显示动作的当前图片索引
        auto paths = this->action_map.value(this->cur_role_act);

        this->cur_role_pix = paths[index++ % paths.size()];

        this->update();
    } );

    showActAnimation(Act::Blink);


    /*设置窗口顶层让图标消失
    this->setWindowFlags(this->windowFlags() |Qt::Tool);
    */

    /*  老版设置定时器
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout,this,&MainWindow::showMovie);
        timer->start(500);
    */

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
        //qDebug() << "Mouse Move Event:" << event->pos();

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
    m_pos = event->globalPosition().toPoint()-this->pos();
}

/*
    功能： 鼠标移动
    参数：void
    返回值：void
*/
void MainWindow::enterEvent(QEvent *event)
{
    qDebug() << "Mouse Move Event:" ;
}

// /*
//     功能： 动画显示
//     参数：void
//     返回值：void
// */
// void MainWindow::showMovie()
// {

// }

// /*
//     功能： 动画显示
//     参数：void
//     返回值：void
// */
// void MainWindow::showMovie1()
// {

// }

// /*
//     功能： 动画显示
//     参数：void
//     返回值：void
// */
// void MainWindow::showMovie2()
// {

// }

// /*
//     功能： 动画显示
//     参数：void
//     返回值：void
// */
// void MainWindow::showMovie3()
// {

// }

// /*
//     功能： 动画显示
//     参数：void
//     返回值：void
// */
// void MainWindow::showMovie3Move()
// {

// }

/*
    功能： 加载图片, 将动作映射到Map中
    参数：void
    返回值：void
*/
void MainWindow::loadRoleActRes()
{
    /*
        功能： 用lambda表达式加载图片, 将动作映射到Map中
        参数：Act::RoleAct act,QString path, int count
            - Act::RoleAct act 传递动作类型
            - QString path 传递图片地址
            - int count 传递图片数量
        返回值：void
    */
    auto addRes = [this](Act::RoleAct act,QString path, int count) {
        QList<QUrl> paths;
        //算法训练之字符串拼接
        for (int i = 1; i <= count; ++i) {
            QString buf(path);
            buf += QString::fromStdString(std::to_string(i));
            buf += QString::fromStdString(".png");
            //QUrl::fromLocalFile(buf) 将本地文件转换成QUrl类型
            paths.append(QUrl::fromLocalFile(buf));
            qDebug() << buf;
        }
        //完成动作与素材间的映射
        action_map.insert(act, paths);
    };
    addRes(Act::Blink,":/sound/img/shime11",3);
}

/*
    功能： 定时器更新
    参数：void
    返回值：void
*/
void MainWindow::showActAnimation(Act::RoleAct act)
{
    timer->stop();

    this->cur_role_act = act;

    timer->start(120);
}

/*
    功能： 绘画显示图像(无背景) => 需要将窗口隐藏
    参数：void
    返回值：void
*/
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //从URl转换为本地图片
    pix.load(this->cur_role_pix.toLocalFile());
    //绘制图片
    painter.drawPixmap(0,0,pix);
}
