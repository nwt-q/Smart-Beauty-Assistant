#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <qDebug>
#include <QContextMenuEvent>
#include <QTimer>
#include <QMap>
#include <QUrl>
#include <QList>
#include <QMenu>
#include <QCursor> // 光标
#include <QMetaEnum>
#include <QtGlobal>
#include <typeinfo>

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
    void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标按下
    void mousePressEvent(QMouseEvent *event) override;
    //鼠标移入
    void enterEvent(QEvent *event);

public slots:
    //加载动画
    void loadRoleActRes();
    // 展示Animation(动画)
    void showActAnimation(Act::RoleAct);
    //接收点击事件切换动作
    void On_MenuTriggered(QAction* act);

private:
    //菜单
    void contextMenuEvent();
    //初始化菜单
    void initMenue();

protected:
    //绘图事件
    void paintEvent(QPaintEvent *);

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

    //菜单属性
    QMenu* menue;

};
#endif // MAINWINDOW_H
