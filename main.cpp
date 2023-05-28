
#include "mainwindow.h"

#include <QApplication>
#include<QLabel>
#include<QMovie>
#include<windows.h>
#include<QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/img/FishBegin.jpg");  /* 设置启动图片 */
    pixmap = pixmap.scaled(500, 300, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    QSplashScreen splash(pixmap); /* 利用QPixmap对象创建一个QSplashScreen对象 */
    splash.show();
    splash.setCursor(Qt::BlankCursor);
    a.processEvents();
    Sleep(3000);
    MainWindow w;
    w.show();
    splash.finish((&w));
    return a.exec();
}

