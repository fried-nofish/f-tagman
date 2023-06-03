#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>

namespace Ui {
class FuncWindow;
}

class FuncWindow : public QMainWindow
{
    Q_OBJECT

public:
    FuncWindow(QWidget *parent = nullptr);
    ~FuncWindow();
    int open_row = 0;
    int open_col = 0;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void shotsign();

    void close_window();

signals:
    void  sendsignal();

private:
    Ui::FuncWindow *ui;
    bool mouse_Flag_Clicked;  //鼠标点击左键
    QPointF screenPos;// 屏幕上的点
};

#endif // FUNCWINDOW_H
