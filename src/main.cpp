
#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //! display startup interface
    auto pixStartup =
        QPixmap(":/img/FishBegin.jpg")
            .scaled(500, 300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QSplashScreen splash(pixStartup, Qt::WindowStaysOnTopHint);
    splash.show();
    splash.setEnabled(false);

    //! preprocess
    MainWindow w;

    QTimer t; //<! using a timer to simulate the preprocess procedure
    t.singleShot(3000, [&]() {
        splash.finish(&w);
        w.show();
    });
    t.start();

    return app.exec();
}
