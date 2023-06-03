
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void read_file();
    void init_title();

private slots:
    void reshow();
    void btn_close_clicked();


private:
    Ui::MainWindow *ui;
    bool mouse_Flag_Clicked;  //鼠标点击左键
    QPointF screenPos;// 屏幕上的点
};

#endif // MAINWINDOW_H
