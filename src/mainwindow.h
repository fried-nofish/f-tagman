
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
} // namespace Ui

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool nativeEvent(
        const QByteArray &eventType, void *message, qintptr *result) override;

protected:
    QString dbPath() const; //<! 本地数据文件路径
    void    loadData();     //<! 加载本地数据
    void    storeData();    //<! 存储本地数据
    void    initialize();

private slots:
    void enterfunc(); //<! 前往功能区

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
