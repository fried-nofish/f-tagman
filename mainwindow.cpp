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
using namespace std;
#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPushButton *newb = new QPushButton(this);
    read_file();


}

MainWindow::~MainWindow()
{
    QFile file(QApplication::applicationDirPath() + "/test.txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
        QTextStream out(&file);
        std::vector<File> a_file = showallfile();
        out<<a_file.size()<<"\n";
        for(auto &it : a_file){
            out<<QString::fromStdString(it.address+"\n");
            std::vector<Tag> taglist;
            taglist = fileshowtag(it);
            out<<taglist.size()<<"\n";
            for(auto itr : taglist){
                out<<QString::fromStdString(itr.name+"\n");
                out<<QString::fromStdString(itr.explain+"\n");
            }
        }

        file.close();

    }
    else{
        qDebug()<<"failed";
    }
    delete ui;
}

void MainWindow::read_file()
{
    QFile file1("test.txt");
    file1.setFileName("test.txt");
    if(file1.open(QIODevice::ReadOnly|QIODevice::Text)){
        //第二种方式就是一数据流读取文件内容
        QDataStream in(&file1);
        QString str = file1.readLine();
        str = str.trimmed();
        int file_num = str.toInt();
        qDebug()<<file_num;
        while(file_num--){

            int tag_num;
            QString file_name = file1.readLine();
            file_name = file_name.trimmed();
            str = file1.readLine();
            str = str.trimmed();
            tag_num = str.toInt();
            qDebug()<<tag_num;
            while(tag_num--){
                QString tag_name = file1.readLine();
                tag_name = tag_name.trimmed();
                qDebug()<<tag_name;
                QString tag_explain = file1.readLine();
                tag_explain = tag_explain.trimmed();
                qDebug()<<tag_explain;

                string newfile_path=file_name.toStdString();
                std::filesystem::path newfile(newfile_path);
                string newfile_name=newfile.filename().string();


                fileaddtag(fileinset(newfile_name,newfile_path),taginvec(tag_name.toStdString(),tag_explain.toStdString()));
            }
        }


        file1.close();

    }else{
        qDebug()<<file1.errorString();
    }
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
        for(const auto &i : taglist){
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
            int result = deletewindow->exec();
            if(result){
                int index=deletewindow->num;
                filedeltag(fileinset(newfile_name,newfile_path),taginvec(taglist[index].name,""));
            }

        }
        else{
            QMessageBox::information(this, "警告","当前文件没有标签");

        }

    }
}




