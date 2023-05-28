#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "api.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    int num=0;
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void init(std::vector<Tag>);

private:
    Ui::Dialog *ui;


public slots:
    void on_comboBox_activated(int index);
};

#endif // DIALOG_H
