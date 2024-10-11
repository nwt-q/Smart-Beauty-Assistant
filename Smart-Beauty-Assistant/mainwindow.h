#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qDebug>
#include <QTimer>
#include <QMap>
#include <QUrl>
#include <QList>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

namespace Act{

//注册枚举命名空间
Q_NAMESPACE

//枚举动作类型
enum RoleAct{
        Sleep,
        Drowse, // 昏昏欲睡
        Work,  //走路
        Drag, //拖拽 , 鼠标滑动
        Blink // 眨眼睛
    };
    Q_ENUM_NS_IMPL(RoleAct)
}


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标按下
    void mousePressEvent(QMouseEvent *event);
    //鼠标移入
    void enterEvent(QEvent *event);

public slots:
    // //显示眨眼动画
    // void showMovie();
    // //显示动画1 打瞌睡
    // void showMovie1();
    // //显示动画2 睡觉
    // void showMovie2();
    // //显示动画3 走路
    // void showMovie3();
    // //显示动画4 拖拽
    // void showMovie3Move();
    //加载动画
    void loadRoleActRes();
    // 展示Animation(动画)
    void showActAnimation(Act::RoleAct);

private:
    Ui::MainWindow *ui;

    //鼠标按下的分量
    QPoint m_pos;

    //窗口目前的位置
    QPoint current_pos;

    //动画的定时器
    QTimer *timer;

    //新型存放图片的形式
    QMap<Act::RoleAct,QList<QUrl>> action_map;

    //记录动作类型: 建立映射关系
    Act::RoleAct cur_role_act;
    //记录当前所用动作
    QUrl cur_role_pix;

    //存放图片后续更改图片更方便
    QPixmap pix;

    //绘图事件
    void paintEvent(QPaintEvent *);

    //动画地址
    QString pic_adrress;
    QString pic_adrress_1 = ":/sound/img/shime11";
    QString pic_adrress_2 = ":/sound/img/shime22";
    QString pic_adrress_3 = ":/sound/img/shime33";
    QString pic_adrress_4 = ":/sound/img/shime44";

};
#endif // MAINWINDOW_H
