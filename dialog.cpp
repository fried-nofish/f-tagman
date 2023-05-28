#include "dialog.h"
#include "ui_dialog.h"
#include <QString>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::init(std::vector<Tag> taglist) {
    for (auto &it : taglist) {
        ui->comboBox->addItem(QString::fromStdString(it.name));
    }
}

void Dialog::on_comboBox_activated(int index) {
    this->num = index;
}
