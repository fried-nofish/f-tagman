#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include<QWidget>
#include "funcwindow.h"
#include "qpushbutton.h"
#include "ui_funcwindow.h"
#include "api.h"
#include "dialog.h"



FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FuncWindow)
{
    ui->setupUi(this);
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

    //创建4个push button对象
    QPushButton *btn_addtag = new QPushButton(this);
    QPushButton *btn_deltag = new QPushButton(this);
    QPushButton *btn_viewtag = new QPushButton(this);
    QPushButton *btn_findfile = new QPushButton(this);

    //设置按钮图案
    QPixmap pix_btn_addtag;
    QPixmap pix_btn_deltag;
    QPixmap pix_btn_viewtag;
    QPixmap pix_btn_findfile;

    pix_btn_addtag.load(":/img/addtag.jpg");
    pix_btn_deltag.load(":/img/deltag.jpg");
    pix_btn_viewtag.load(":/img/viewtag.jpg");
    pix_btn_findfile.load(":/img/findfile.jpg");

    pix_btn_addtag = pix_btn_addtag.scaled(100,100,Qt::KeepAspectRatio);
    pix_btn_deltag = pix_btn_deltag.scaled(100,100,Qt::KeepAspectRatio);
    pix_btn_viewtag = pix_btn_viewtag.scaled(100,100,Qt::KeepAspectRatio);
    pix_btn_findfile = pix_btn_findfile.scaled(100,100,Qt::KeepAspectRatio);

    //将四个按钮加入布局中
    btn_addtag->move(50,250);
    btn_deltag->move(50,400);
    btn_viewtag->move(180,250);
    btn_findfile->move(180,400);


    //图片自适应
    btn_addtag->setFixedSize(pix_btn_addtag.size());
    btn_deltag->setFixedSize(pix_btn_deltag.size());
    btn_viewtag->setFixedSize(pix_btn_viewtag.size());
    btn_findfile->setFixedSize(pix_btn_findfile.size());

    btn_addtag->setStyleSheet("border-image:url(:/img/addtag.jpg);");
    btn_deltag->setStyleSheet("border-image:url(:/img/deltag.jpg);");
    btn_viewtag->setStyleSheet("border-image:url(:/img/viewtag.jpg);");
    btn_findfile->setStyleSheet("border-image:url(:/img/findfile.jpg);");


    //设置触发条件
    connect(btn_addtag,&QPushButton::clicked,this,&FuncWindow::on_pushButton_3_clicked);
    connect(btn_deltag,&QPushButton::clicked,this,&FuncWindow::on_pushButton_4_clicked);
    connect(btn_viewtag,&QPushButton::clicked,this,&FuncWindow::on_pushButton_2_clicked);
    connect(btn_findfile,&QPushButton::clicked,this,&FuncWindow::on_pushButton_clicked);

    //关闭窗口按钮
    QPushButton * btn_close = new QPushButton;
    btn_close->setParent(this);
    btn_close->move(950, 15);
    QPixmap pix_btn_close;
    pix_btn_close.load(":/img/close.png");
    btn_close->setFixedSize(25, 25);
    btn_close->setStyleSheet("border-image:url(:/img/close.png);");
    connect(btn_close, &QPushButton::clicked, this, &FuncWindow::shotsign);
    connect(this,SIGNAL(sendsignal()),this,SLOT(close_window()));
    connect(ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(changeTest(int, int)));
}

FuncWindow::~FuncWindow()
{
    delete ui;
}

void FuncWindow::on_pushButton_clicked()
{
    Dialog *deletewindow = new Dialog;
    std::vector<Tag> taglist = showalltag();
    deletewindow->init(taglist);
    int result = deletewindow->exec();
    if(result){
        if(taglist.size()==0)return;
        int index=deletewindow->num;

        ui->tableWidget->setRowCount(0);
        int row_num = 0;
        for(auto &i : taglist[index].T_filelist){

            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(row_num,0,new QTableWidgetItem(QString::fromStdString(taglist[index].name)));
            ui->tableWidget->item(row_num,0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(row_num,1,new QTableWidgetItem(QString::fromStdString(i.address)));
            ui->tableWidget->item(row_num,1)->setCheckState(Qt::Unchecked);
        }
    }
}

void FuncWindow::on_pushButton_2_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){


        ui->tableWidget->setRowCount(0);
        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file("","");
        file.name =  newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist = fileshowtag(file);
        int row_num = 0;
        for(const auto &i : taglist){

            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(row_num,0,new QTableWidgetItem(QString::fromStdString(i.name+" "+i.explain)));
            ui->tableWidget->item(row_num,0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(row_num,1,new QTableWidgetItem(fileName));
            ui->tableWidget->item(row_num,1)->setCheckState(Qt::Unchecked);
            row_num++;
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
        if(bOk)fileaddtag(fileinset(newfile_name,newfile_path),taginvec(sName.toStdString(),""));
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
        ui->tableWidget->setRowCount(0);
        taglist = fileshowtag(file);
        int row_num = 0;
        for(const auto &i : taglist){
            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(row_num,0,new QTableWidgetItem(QString::fromStdString(i.name+" "+i.explain)));
            ui->tableWidget->item(row_num,0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(row_num,1,new QTableWidgetItem(fileName));
            ui->tableWidget->item(row_num,1)->setCheckState(Qt::Unchecked);
            row_num++;
        }

    }
}

void FuncWindow::shotsign()
{
    emit sendsignal();
}

void FuncWindow::close_window()
{
    this->close();
}
