#include "mainwindow.h"
#include <QApplication>

// BOOL CALLBACK ShowWindowsProc(HWND hwnd, LPARAM lParam) {
//     wchar_t szTitle[MAX_PATH] = {0};
//     GetWindowText(hwnd,szTitle, MAX_PATH);
//     return TRUE;
// }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //系统图标
    QSystemTrayIcon sysTray(QIcon(":/sound/other/btn1.png"),&w);

    QMenu menu;
    auto showAct = new QAction("show", &sysTray);
    auto exitAct = new QAction("exit", &sysTray);
    QObject::connect(showAct, &QAction::triggered, [&](){
        w.setVisible(true);
    });
    QObject::connect(exitAct, &QAction::triggered, [&](){
        QApplication::quit();
    });
    menu.addAction(showAct);
    menu.addAction(exitAct);
    sysTray.setContextMenu(&menu);
    sysTray.show();

    w.show();
    return a.exec();
}
