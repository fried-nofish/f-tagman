#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include "funcwindow.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "api.h"



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
        while(file_num--){

            int tag_num;
            QString file_name = file1.readLine();
            file_name = file_name.trimmed();
            str = file1.readLine();
            str = str.trimmed();
            tag_num = str.toInt();
            while(tag_num--){
                QString tag_name = file1.readLine();
                tag_name = tag_name.trimmed();
                QString tag_explain = file1.readLine();
                tag_explain = tag_explain.trimmed();

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPushButton *newb = new QPushButton(this);
    read_file();
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
    this->setStyleSheet("QMainWindow {border-image:url(:/img/start_interface.jpg)}");

    //立即使用按钮
    QPushButton * btn_start = new QPushButton;
    btn_start->setParent(this);
    //设置按钮位置
    btn_start->move(500, 420);
    QPixmap pix_btn_start;
    pix_btn_start.load(":/img/startbutton.png");
    //根据图片的最大矩形大小设置按钮大小，使图片与按钮相适应
    btn_start->setFixedSize(pix_btn_start.size());
    //使用border-image可使图片自适应
    btn_start->setStyleSheet("border-image:url(:/img/startbutton.png);");
    //设置按钮背景透明
    //btn->setFlat(true);

    //关闭窗口按钮
    QPushButton * btn_close = new QPushButton;
    btn_close->setParent(this);
    btn_close->move(950, 15);
    QPixmap pix_btn_close;
    pix_btn_close.load(":/img/close.png");
    btn_close->setFixedSize(25, 25);
    btn_close->setStyleSheet("border-image:url(:/img/close.png);");
    connect(btn_close, &QPushButton::clicked, this, &MainWindow::close);
    connect(btn_start, SIGNAL(clicked()),this,SLOT(on_btn_close_clicked()));
}

MainWindow::~MainWindow(){
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
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    //移动窗口
    if(mouse_Flag_Clicked){
        //Qt6建议使用globalPosition,返回的是float类型,而globaPos返回的是int类型
        //均需要添加头文件<QMouseEvent>
        QPointF tempPos = event->globalPosition() - screenPos;

        //move函数用的是int类型,所以需要将QPointF转换成QPoint
        QPoint transPos = tempPos.toPoint();
        move(pos() + transPos);
        screenPos = event->globalPosition();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        mouse_Flag_Clicked = true;
        screenPos = event->globalPosition();
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_Flag_Clicked = false;
}

void MainWindow::on_btn_close_clicked()
{
    this->hide();
    FuncWindow *con = new FuncWindow;
    connect(con,SIGNAL(sendsignal()),this,SLOT(reshow()));
    con->show();

}

void MainWindow::reshow()
{
    this->show();
}



