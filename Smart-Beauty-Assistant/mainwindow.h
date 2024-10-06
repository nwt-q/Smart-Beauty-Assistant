#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
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
    //显示眨眼动画
    void showMovie();
    //显示动画1 打瞌睡
    void showMovie1();
    //显示动画2 睡觉
    void showMovie2();
    //显示动画3 走路
    void showMovie3();
    //显示动画4 拖拽
    void showMovie3Move();

private:
    Ui::MainWindow *ui;

    //眨眼动画的定时器
    QTimer *timer;

    //绘图事件
    void paintEvent(QPaintEvent *);


};
#endif // MAINWINDOW_H
