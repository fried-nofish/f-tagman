#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QWidget>

namespace Ui {
class newWindow;
} // namespace Ui

class newWindow : public QWidget {
    Q_OBJECT

public:
    explicit newWindow(QWidget *parent = nullptr);
    ~newWindow();

private:
    Ui::newWindow *ui;

signals:
    void sendsignal();
private slots:
    void on_pushButton_clicked();
};

#endif // NEWWINDOW_H
