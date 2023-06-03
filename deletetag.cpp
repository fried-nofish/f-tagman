#include "deletetag.h"
#include "ui_deletetag.h"


DeleteTag::DeleteTag(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteTag)
{
    ui->setupUi(this);
}

DeleteTag::~DeleteTag()
{
    delete ui;
}

void DeleteTag::init(std::vector<Tag> taglist)
{
    for(auto &it : taglist){
        ui->comboBox->addItem(QString::fromStdString(it.name));
    }
}

void DeleteTag::on_pushButton_clicked()
{
    this->hide();
}


void DeleteTag::on_comboBox_activated(int index)
{
    this->num=index;
}


