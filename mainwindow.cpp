#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
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

void MainWindow::init_title()
{
    this->setWindowIcon(QIcon(":/img/logo.jpg"));
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
        btn_start->move(495, 435);
        QPixmap pix_btn_start;
        pix_btn_start.load(":/img/startbutton.png");
        pix_btn_start = pix_btn_start.scaled(250, 250, Qt::KeepAspectRatio);
        //根据图片的最大矩形大小设置按钮大小，使图片与按钮相适应
        btn_start->setFixedSize(pix_btn_start.size());
        //使用border-image可使图片自适应
        btn_start->setStyleSheet("border-image:url(:/img/startbutton.png);");
        connect(btn_start, SIGNAL(clicked()),this,SLOT(btn_close_clicked()));

        //关闭窗口按钮
        QPushButton * btn_close = new QPushButton;
        btn_close->setParent(this);
        btn_close->move(960, 15);
        QPixmap pix_btn_close;
        pix_btn_close.load(":/img/close.png");
        btn_close->setFixedSize(23, 23);
        btn_close->setStyleSheet("border-image:url(:/img/close.png);");
        connect(btn_close, &QPushButton::clicked, this, &MainWindow::close);

        //缩小窗口按钮
        QPushButton * btn_off_screen = new QPushButton;
        btn_off_screen->setParent(this);
        btn_off_screen->move(920, 15);
        QPixmap pix_btn_off_screen;
        pix_btn_off_screen.load(":/img/off_screen.png");
        btn_off_screen->setFixedSize(23, 23);
        btn_off_screen->setStyleSheet("border-image:url(:/img/off_screen.png);");
        connect(btn_off_screen, &QPushButton::clicked, this, &MainWindow::showMinimized);

        //更多窗口按钮
        QPushButton * btn_more = new QPushButton;
        btn_more->setParent(this);
        btn_more->move(880, 15);
        QPixmap pix_btn_more;
        pix_btn_more.load(":/img/hamburger_button.png");
        btn_more->setFixedSize(23, 23);
        btn_more->setStyleSheet("border-image:url(:/img/hamburger_button.png);");

        //加按钮的菜单栏
        QMenu *more_menu=new QMenu;
        QAction *action1 = new QAction(QIcon(":/img/config.png"), "设置");
        QAction *action2 = new QAction(QIcon(":/img/advice.png"), "意见反馈");
        QAction *action3 = new QAction(QIcon(":/img/about_us.png"), "关于我们");
        more_menu->addAction(action1);
        more_menu->addSeparator();
        more_menu->addAction(action2);
        more_menu->addSeparator();
        more_menu->addAction(action3);
        btn_more->setMenu(more_menu);
        //btn_more->setStyleSheet("QPushButton::menu-indicator{image:none}");
        //QHBoxLayout *mainLayout=new QHBoxLayout(this);
        //mainLayout->addWidget(mybtn);

        //主题窗口按钮
        QPushButton * btn_theme = new QPushButton;
        btn_theme->setParent(this);
        btn_theme->move(840, 15);
        QPixmap pix_btn_theme;
        pix_btn_theme.load(":/img/theme.png");
        btn_theme->setFixedSize(23, 23);
        btn_theme->setStyleSheet("border-image:url(:/img/theme.png);");

        //设置主页面文字
        QLabel *label1 = new QLabel;
        label1->setParent(this);
        label1->setText(QString("深度管理，轻松找到"));
        label1->setGeometry(400, 230, 700, 100);
        //设置字体颜色
        label1->setStyleSheet("color:rgb(0, 122, 255)");
        //设置字体样式,字体大小和加粗权重
        QFont font("微软雅黑", 45, 10);
        label1->setFont(font);

        //主页面文字2
        QLabel *label2 = new QLabel;
        label2->setParent(this);
        label2->setText(QString("如果你也觉得本系统好用的话，那我觉得这件事，泰裤辣！"));
        label2->setGeometry(400, 310, 700, 100);
        label2->setStyleSheet("color:rgb(117, 117, 209)");
        QFont font2("微软雅黑", 15, 0);
        label2->setFont(font2);

        //窗口标题
        QLabel *label3 = new QLabel;
        label3->setParent(this);
        label3->setText(QString("文件标签管理系统"));
        label3->setGeometry(30, -5, 300, 50);
        label3->setStyleSheet("color:rgb(255, 255, 255)");
        QFont font3("微软雅黑", 12, 0);
        label3->setFont(font3);

        //左上角logo
        QPixmap pix_logo;
        pix_logo.load(":/img/logo.jpg");
        QLabel *label4 = new QLabel;
        label4->setParent(this);
        label4->setGeometry(0, 5, 30, 30);
        //label4->setPixmap(pix_logo);
        label4->setStyleSheet("border-image:url(:/img/logo.jpg);");
    }

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    //    QPushButton *newb = new QPushButton(this);
        read_file();

        init_title();
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
            for(auto &itr : taglist){
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

void MainWindow::btn_close_clicked()
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




