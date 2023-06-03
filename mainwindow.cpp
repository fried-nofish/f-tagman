#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "newwindow.h"
#include "api.h"
#include "dialog.h"
#include <iostream>
using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    QPushButton *newb = new QPushButton(this);

    QFile file(QApplication::applicationDirPath() + "/test.txt");



}

MainWindow::~MainWindow()
{
    QFile file(QApplication::applicationDirPath() + "/test.txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QTextStream out(&file);
        std::vector<File> a_file = showallfile();
        qDebug()<<a_file.size()<<"\n";
        for(auto &it : a_file){
            out<<QString::fromStdString(it.address+"\n");
        }
        out<<"done";
        file.close();
        qDebug()<<"done";

    }
    else{
        qDebug()<<"failed";
    }
    delete ui;
}

void MainWindow::reshow()
{
    this->show();
}



void MainWindow::on_pushButton_clicked()
{
    this->hide();
    newWindow *con = new newWindow;
    connect(con,SIGNAL(sendsignal()),this,SLOT(reshow()));
    con->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this,tr("打开文件"),"./",tr("All file (*.*)"));
    if(!fileName.isEmpty()){

        ui->textEdit->clear();
        string newfile_path=fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string newfile_name=newfile.filename().string();
        File file("","");
        file.name =  newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist = fileshowtag(file);
        for(auto i : taglist){
            ui->textEdit->insertPlainText(QString::fromStdString(i.name+" "+i.explain));
        }
    }
}




void MainWindow::on_pushButton_3_clicked()
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



void MainWindow::on_pushButton_4_clicked()
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
            deletewindow->exec();

            int index=deletewindow->num;
            filedeltag(fileinset(newfile_name,newfile_path),taginvec(taglist[index].name,""));
        }
        else{
            QMessageBox::information(this, "警告","当前文件没有标签");

        }

    }
}




