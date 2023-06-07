#ifndef FUNCWINDOW_H
#define FUNCWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class FuncWindow;
} // namespace Ui

class FuncWindow : public QMainWindow {
    Q_OBJECT

public:
    FuncWindow(QWidget *parent = nullptr);
    ~FuncWindow();

protected:
    void initialize();
    void setupUi();
    void initializeButtons();

private:
    QPushButton *addButton(QPoint p, QSize size, const QString &imageUrl);

signals:
    void closed();

private slots:
    void addTag();      //<! 添加标签
    void removeTag();   //<! 移除标签
    void displayTags(); //<! 显示标签
    void findFile();    //<! 查找文件
    void renameTag();   //<! 标签重命名
    void explain();     //<! 解释标签
    void openFile();    //<! 打开文件
    void updateCheckState(int row, int col);

private:
    Ui::FuncWindow *ui;
    QPushButton    *btn_openfile;
    int             open_row = 0;
    int             open_col = 0;
};

#endif // FUNCWINDOW_H
