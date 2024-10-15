#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <string>

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
        index %= paths.size();
        this->cur_role_pix = paths[index++ % paths.size()];

        //qDebug() << index ;

        this->update();
    } );

    //初始化动作
    showActAnimation(Act::Work);


    initMenue();

    /*设置窗口顶层让图标消失
    this->setWindowFlags(this->windowFlags() |Qt::Tool);
    */

    start_ai();
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
    //鼠标右键 与 点击 与移动
    if (event->type() == QEvent::MouseMove) {
        //qDebug() << "Mouse Move Event:" << event->pos();

        //移动窗口
        /*
         *  this->current_pos = QPoint(e->globalPos()-m_pos);
         *  this->move(e->globalPos()-this->m_pos);
        */
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

    if(event->button() == Qt::RightButton) { //无论左键右键都识别到
        menue->exec(QCursor::pos());
        //点击 = 左键 or 右键  or 中键
        qDebug() <<  event->type();
    } else {
        //鼠标按下记录分量
        m_pos = event->globalPosition().toPoint()-this->pos();
    }
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
            //qDebug() << buf;
        }
        //完成动作与素材间的映射
        action_map.insert(act, paths);
    };

    addRes(Act::Blink,":/sound/img/shime11",3);
    addRes(Act::Drag,":/sound/img/shime22",5);
    addRes(Act::Sleep,":/sound/img/shime33",7);
    addRes(Act::Work,":/sound/img/shime44",2);
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

    timer->start(240);
}

/*
    功能： 切换点击事件
    参数：QAction *action
    返回值：void
*/
void MainWindow::On_MenuTriggered(QAction* act)
{
    QMetaEnum List = QMetaEnum::fromType<Act::RoleAct>();

    for (int i = 0; i < List.keyCount(); ++i) {
        qDebug() << List.key(i); // 打印枚举的键名
    }
    qDebug() << act->text();

    QString Action = act->text();
    if (Action == "眨眼") {
        showActAnimation(Act::Blink);
    } else if (Action == "昏昏欲睡") {
        showActAnimation(Act::Drag);
    } else if (Action == "睡觉") {
        showActAnimation(Act::Sleep);
    } else if (Action == "走路") {
        showActAnimation(Act::Work);
    } else {
        // 默认情况
    }
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

/*
    功能： 菜单
    参数：void
    返回值：void
*/
void MainWindow::contextMenuEvent()
{
    //this->menue->popup(QCursor::pos());
    qDebug() << " 1";
}

/*
    功能： 初始化菜单
    参数：void
    返回值：void
*/
void MainWindow::initMenue()
{
    // contextMenuEvent();


    //connect(this->menue,&QMenu::triggered,this,&MainWindow::On_MenuTriggered);

    menue = new QMenu("动作");

    QMenuBar* menubar = this->menuBar();

    this->setMenuBar(menubar);
    menubar->hide();

    //添加菜单到菜单栏中
    menubar->addMenu(menue);

    //创建菜单项
    QAction* action1 = new QAction(QIcon(":/sound/other/btn1.png"),"眨眼");
    QAction* action2 = new QAction(QIcon(":/sound/other/btn1.png"),"昏昏欲睡");
    QAction* action3 = new QAction(QIcon(":/sound/other/btn1.png"),"睡觉");
    QAction* action4 = new QAction(QIcon(":/sound/other/btn1.png"),"走路");
    QAction * action5 = new QAction(QIcon(":/sound/other/btn1.png"),"隐藏");

    //添加菜单项到菜单中
    menue->addAction(action1);
    menue->addAction(action2);
    menue->addAction(action3);
    menue->addAction(action4);
    menue->addAction(action5);


    //connect(this->menue,&QMenu::triggered,this,&MainWindow::On_MenuTriggered);
    connect(action1, &QAction::triggered,[this](){
        showActAnimation(Act::Blink);
    });
    connect(action2, &QAction::triggered,[this](){
        showActAnimation(Act::Drag);
    });
    connect(action3, &QAction::triggered,[this](){
        showActAnimation(Act::Sleep);
    });
    connect(action4, &QAction::triggered,[this](){
        showActAnimation(Act::Work);
    });
    connect(action5, &QAction::triggered,[this](){
        this->setVisible(false);
    });
}

/*
    功能：调用ai模块
    参数：void
    返回值：void
*/
void MainWindow::start_ai()
{
    Ai_Module* GML = new Ai_Module();
    GML->SendJsonData();
}
