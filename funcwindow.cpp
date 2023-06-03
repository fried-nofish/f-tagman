#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "funcwindow.h"
#include "qpushbutton.h"
#include "ui_funcwindow.h"
#include "newwindow.h"
#include "api.h"
#include "dialog.h"



FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FuncWindow)
{
    ui->setupUi(this);
    //    QPushButton *newb = new QPushButton(this);
    //设置应用程序图标
    this->setWindowIcon(QIcon(":/img/logo.png"));
    //隐藏标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pix_bk;
    pix_bk.load(":/img/start_interface.jpg");
    //设置图片像素为1000*1000(把图片缩小了),设置图片保持宽高比
    pix_bk = pix_bk.scaled(1000, 1000, Qt::KeepAspectRatio);
    //设置窗口大小为图片大小
    this->setFixedSize(pix_bk.size());
    //border-image使图片自适应
    this->setStyleSheet("QMainWindow {border-image:url(:/img/fun_interface.jpg)}");

    //关闭窗口按钮
    QPushButton * btn_close = new QPushButton;
    btn_close->setParent(this);
    btn_close->move(950, 15);
    QPixmap pix_btn_close;
    pix_btn_close.load(":/img/close.png");
    btn_close->setFixedSize(25, 25);
    btn_close->setStyleSheet("border-image:url(:/img/close.png);");
    connect(btn_close, &QPushButton::clicked, this, &FuncWindow::close);
}

FuncWindow::~FuncWindow()
{
    delete ui;
}


void FuncWindow::on_pushButton_2_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){

        //ui->textEdit->clear();
        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file("","");
        file.name =  newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist = fileshowtag(file);
        for(const auto &i : taglist){
           // ui->textEdit->insertPlainText(QString::fromStdString(i.name+" "+i.explain));
        }
    }
}




void FuncWindow::on_pushButton_3_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){


        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file("","") ;
        file.name =  newfile_name;
        file.address = newfile_path;

        bool bOk = false;
        QString sName = QInputDialog::getText(this,
                                              "QInputdialog_Name",
                                              "标签名",
                                              QLineEdit::Normal,
                                              "",
                                              &bOk
                                              );
        fileaddtag(fileinset(newfile_name,newfile_path),taginvec(sName.toStdString(),""));
    }

}



void FuncWindow::on_pushButton_4_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){


        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file("","") ;
        file.name =  newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist = fileshowtag(file);
        if(!taglist.empty()){
            Dialog *deletewindow = new Dialog;

            deletewindow->init(taglist);
            int result = deletewindow->exec();
            if(result){
                int index=deletewindow->num;
                filedeltag(fileinset(newfile_name,newfile_path),taginvec(taglist[index].name,""));
            }

        }
        else{
            QMessageBox::information(this, "警告","当前文件没有标签");

        }
       // ui->textEdit->clear();
        taglist = fileshowtag(file);
        for(auto i : taglist){
         //   ui->textEdit->insertPlainText(QString::fromStdString(i.name+" "+i.explain));
        }

    }
}


