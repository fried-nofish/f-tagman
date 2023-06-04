#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>
#include <QLabel>
#include <QProcess>
#include "funcwindow.h"
#include "qpushbutton.h"
#include "ui_funcwindow.h"
#include "api.h"
#include "dialog.h"

FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FuncWindow) {
    ui->setupUi(this);
    init_title();
    init_btn();

    //    ui->tableWidget->verticalScrollBar();

    QScrollBar *vScrollBar = ui->tableWidget->verticalScrollBar();
    if (vScrollBar != NULL) {
        vScrollBar->setValue(ui->tableWidget->verticalScrollBar()->maximum());
    }
    connect(
        ui->tableWidget,
        SIGNAL(cellChanged(int, int)),
        this,
        SLOT(changeTest(int, int)));
}

FuncWindow::~FuncWindow() {
    delete ui;
}

void FuncWindow::init_btn() {
    // 创建5个push button对象
    QPushButton *btn_addtag    = new QPushButton(this);
    QPushButton *btn_deltag    = new QPushButton(this);
    QPushButton *btn_viewtag   = new QPushButton(this);
    QPushButton *btn_findfile  = new QPushButton(this);
    QPushButton *btn_renametag = new QPushButton(this);
    QPushButton *btn_explain   = new QPushButton(this);
    btn_openfile               = new QPushButton(this);
    btn_openfile->setEnabled(0);

    // 设置按钮图案
    QPixmap pix_btn_addtag;
    QPixmap pix_btn_deltag;
    QPixmap pix_btn_viewtag;
    QPixmap pix_btn_findfile;
    QPixmap pix_btn_renametag;
    QPixmap pix_btn_explain;
    QPixmap pix_btn_openfile;

    pix_btn_addtag.load(":/img/addtag.png");
    pix_btn_deltag.load(":/img/deltag.png");
    pix_btn_viewtag.load(":/img/viewtag.png");
    pix_btn_findfile.load(":/img/findfile.png");
    pix_btn_renametag.load(":/img/renametag.png");
    pix_btn_explain.load(":/img/explain.png");
    pix_btn_openfile.load(":/img/turn_on.png");

    pix_btn_addtag    = pix_btn_addtag.scaled(101, 101, Qt::KeepAspectRatio);
    pix_btn_deltag    = pix_btn_deltag.scaled(105, 105, Qt::KeepAspectRatio);
    pix_btn_viewtag   = pix_btn_viewtag.scaled(110, 110, Qt::KeepAspectRatio);
    pix_btn_findfile  = pix_btn_findfile.scaled(108, 108, Qt::KeepAspectRatio);
    pix_btn_renametag = pix_btn_renametag.scaled(107, 107, Qt::KeepAspectRatio);
    pix_btn_explain   = pix_btn_explain.scaled(107, 107, Qt::KeepAspectRatio);
    pix_btn_openfile  = pix_btn_openfile.scaled(107, 107, Qt::KeepAspectRatio);

    // 将四个按钮加入布局中
    btn_addtag->move(80, 80);
    btn_deltag->move(260, 80);
    btn_viewtag->move(440, 80);
    btn_findfile->move(620, 80);
    btn_renametag->move(800, 80);
    btn_explain->move(840, 400);
    btn_openfile->move(840, 220);

    // 图片自适应
    btn_addtag->setFixedSize(pix_btn_addtag.size());
    btn_deltag->setFixedSize(pix_btn_deltag.size());
    btn_viewtag->setFixedSize(pix_btn_viewtag.size());
    btn_findfile->setFixedSize(pix_btn_findfile.size());
    btn_renametag->setFixedSize(pix_btn_renametag.size());
    btn_explain->setFixedSize(pix_btn_explain.size());
    btn_openfile->setFixedSize(pix_btn_openfile.size());

    btn_addtag->setStyleSheet("border-image:url(:/img/addtag.png);");
    btn_deltag->setStyleSheet("border-image:url(:/img/deltag.png);");
    btn_viewtag->setStyleSheet("border-image:url(:/img/viewtag.png);");
    btn_findfile->setStyleSheet("border-image:url(:/img/findfile.png);");
    btn_renametag->setStyleSheet("border-image:url(:/img/renametag.png);");
    btn_explain->setStyleSheet("border-image:url(:/img/explain.png);");
    btn_openfile->setStyleSheet("border-image:url(:/img/turn_on.png);");

    // 设置触发条件
    connect(
        btn_addtag,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_3_clicked);
    connect(
        btn_deltag,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_4_clicked);
    connect(
        btn_viewtag,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_2_clicked);
    connect(
        btn_findfile,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_clicked);
    connect(
        btn_renametag,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_5_clicked);
    connect(
        btn_openfile,
        &QPushButton::clicked,
        this,
        &FuncWindow::on_pushButton_6_clicked);
}

void FuncWindow::init_title() {
    this->setWindowIcon(QIcon(":/img/logo.jpg"));
    // 隐藏标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pix_bk;
    pix_bk.load(":/img/start_interface.jpg");
    // 设置图片像素为1000*1000(把图片缩小了),设置图片保持宽高比
    pix_bk = pix_bk.scaled(1000, 1000, Qt::KeepAspectRatio);
    // 设置窗口大小为图片大小
    this->setFixedSize(pix_bk.size());
    // border-image使图片自适应
    this->setStyleSheet(
        "QMainWindow {border-image:url(:/img/fun_interface.jpg)}");

    // 关闭窗口按钮
    QPushButton *btn_close = new QPushButton;
    btn_close->setParent(this);
    btn_close->move(950, 15);
    QPixmap pix_btn_close;
    pix_btn_close.load(":/img/close.png");
    btn_close->setFixedSize(25, 25);
    btn_close->setStyleSheet("border-image:url(:/img/close.png);");
    connect(btn_close, &QPushButton::clicked, this, &FuncWindow::shotsign);
    connect(this, SIGNAL(sendsignal()), this, SLOT(close_window()));

    // 缩小窗口按钮
    QPushButton *btn_off_screen = new QPushButton;
    btn_off_screen->setParent(this);
    btn_off_screen->move(920, 15);
    QPixmap pix_btn_off_screen;
    pix_btn_off_screen.load(":/img/off_screen.png");
    btn_off_screen->setFixedSize(23, 23);
    btn_off_screen->setStyleSheet("border-image:url(:/img/off_screen.png);");
    connect(
        btn_off_screen,
        &QPushButton::clicked,
        this,
        &FuncWindow::showMinimized);

    // 更多窗口按钮
    QPushButton *btn_more = new QPushButton;
    btn_more->setParent(this);
    btn_more->move(880, 15);
    QPixmap pix_btn_more;
    pix_btn_more.load(":/img/hamburger_button.png");
    btn_more->setFixedSize(23, 23);
    btn_more->setStyleSheet("border-image:url(:/img/hamburger_button.png);");

    // 加按钮的菜单栏
    QMenu   *more_menu = new QMenu;
    QAction *action1   = new QAction(QIcon(":/img/config.png"), "设置");
    QAction *action2   = new QAction(QIcon(":/img/advice.png"), "意见反馈");
    QAction *action3 = new QAction(QIcon(":/img/about_us.png"), "关于我们");
    more_menu->addAction(action1);
    more_menu->addSeparator();
    more_menu->addAction(action2);
    more_menu->addSeparator();
    more_menu->addAction(action3);
    btn_more->setMenu(more_menu);
    // btn_more->setStyleSheet("QPushButton::menu-indicator{image:none}");
    // QHBoxLayout *mainLayout=new QHBoxLayout(this);
    // mainLayout->addWidget(mybtn);

    // 主题窗口按钮
    QPushButton *btn_theme = new QPushButton;
    btn_theme->setParent(this);
    btn_theme->move(840, 15);
    QPixmap pix_btn_theme;
    pix_btn_theme.load(":/img/theme.png");
    btn_theme->setFixedSize(23, 23);
    btn_theme->setStyleSheet("border-image:url(:/img/theme.png);");

    // 窗口标题
    QLabel *label3 = new QLabel;
    label3->setParent(this);
    label3->setText(QString("文件标签管理系统"));
    label3->setGeometry(30, -5, 300, 50);
    label3->setStyleSheet("color:rgb(255, 255, 255)");
    QFont font3("微软雅黑", 12, 0);
    label3->setFont(font3);

    // 左上角logo
    QPixmap pix_logo;
    pix_logo.load(":/img/logo.jpg");
    QLabel *label4 = new QLabel;
    label4->setParent(this);
    label4->setGeometry(0, 5, 30, 30);
    // label4->setPixmap(pix_logo);
    label4->setStyleSheet("border-image:url(:/img/logo.jpg);");
}

void FuncWindow::on_pushButton_clicked() // 找文件
{
    Dialog          *deletewindow = new Dialog;
    std::vector<Tag> taglist      = showalltag();
    deletewindow->init(taglist);
    int result = deletewindow->exec();
    if (result) {
        if (taglist.size() == 0) return;
        int index = deletewindow->num;

        ui->tableWidget->setRowCount(0);
        int row_num = 0;
        for (auto &i : taglist[index].T_filelist) {
            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(
                row_num,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(taglist[index].name)));
            ui->tableWidget->item(row_num, 0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(
                row_num,
                1,
                new QTableWidgetItem(QString::fromStdString(i.address)));
            ui->tableWidget->item(row_num, 1)->setCheckState(Qt::Unchecked);
        }
    }
}

void FuncWindow::on_pushButton_2_clicked() // 显示标签
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"), "./", tr("All file (*.*)"));
    if (!fileName.isEmpty()) {
        ui->tableWidget->setRowCount(0);
        string                newfile_path = fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string                newfile_name = newfile.filename().string();
        File                  file("", "");
        file.name    = newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist     = fileshowtag(file);
        int row_num = 0;
        for (const auto &i : taglist) {
            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(
                row_num,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(i.name + " " + i.explain)));
            ui->tableWidget->item(row_num, 0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(
                row_num, 1, new QTableWidgetItem(fileName));
            ui->tableWidget->item(row_num, 1)->setCheckState(Qt::Unchecked);
            row_num++;
        }
    }
}

void FuncWindow::on_pushButton_3_clicked() // 添加标签
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"), "./", tr("All file (*.*)"));
    if (!fileName.isEmpty()) {
        string                newfile_path = fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string                newfile_name = newfile.filename().string();
        File                  file("", "");
        file.name    = newfile_name;
        file.address = newfile_path;

        bool    bOk   = false;
        QString sName = QInputDialog::getText(
            this, "QInputdialog_Name", "标签名", QLineEdit::Normal, "", &bOk);
        if (bOk)
            fileaddtag(
                fileinset(newfile_name, newfile_path),
                taginvec(sName.toStdString(), ""));
    }
}

void FuncWindow::on_pushButton_4_clicked() // 删除标签
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("打开文件"), "./", tr("All file (*.*)"));
    if (!fileName.isEmpty()) {
        string                newfile_path = fileName.toStdString();
        std::filesystem::path newfile(newfile_path);
        string                newfile_name = newfile.filename().string();
        File                  file("", "");
        file.name    = newfile_name;
        file.address = newfile_path;
        std::vector<Tag> taglist;
        taglist = fileshowtag(file);
        if (!taglist.empty()) {
            Dialog *deletewindow = new Dialog;

            deletewindow->init(taglist);
            int result = deletewindow->exec();
            if (result) {
                int index = deletewindow->num;
                filedeltag(
                    fileinset(newfile_name, newfile_path),
                    taginvec(taglist[index].name, ""));
            }

        } else {
            QMessageBox::information(this, "警告", "当前文件没有标签");
        }
        ui->tableWidget->setRowCount(0);
        taglist     = fileshowtag(file);
        int row_num = 0;
        for (const auto &i : taglist) {
            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(
                row_num,
                0,
                new QTableWidgetItem(
                    QString::fromStdString(i.name + " " + i.explain)));
            ui->tableWidget->item(row_num, 0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(
                row_num, 1, new QTableWidgetItem(fileName));
            ui->tableWidget->item(row_num, 1)->setCheckState(Qt::Unchecked);
            row_num++;
        }
    }
}

void FuncWindow::on_pushButton_5_clicked() // 标签改名
{
    Dialog          *deletewindow = new Dialog;
    std::vector<Tag> taglist      = showalltag();
    deletewindow->init(taglist);
    int result = deletewindow->exec();
    if (result) {
        if (taglist.size() == 0) return;
        int index = deletewindow->num;

        bool    bOk   = false;
        QString sName = QInputDialog::getText(
            this,
            "QInputdialog_Name",
            "更改的标签名",
            QLineEdit::Normal,
            "",
            &bOk);
        if (bOk)
            tagrename(taglist[index].name, sName.toStdString(), ""); // 标签改名
        ui->tableWidget->setRowCount(0);
        int row_num = 0;
        for (auto &i : taglist[index].T_filelist) {
            ui->tableWidget->insertRow(row_num);
            ui->tableWidget->setItem(row_num, 0, new QTableWidgetItem(sName));
            ui->tableWidget->item(row_num, 0)->setCheckState(Qt::Unchecked);
            ui->tableWidget->setItem(
                row_num,
                1,
                new QTableWidgetItem(QString::fromStdString(i.address)));
            ui->tableWidget->item(row_num, 1)->setCheckState(Qt::Unchecked);
        }
    }
}

void FuncWindow::changeTest(int row, int col) {
    if (ui->tableWidget->item(row, col)->checkState() == Qt::Checked
        && col != 0) {
        open_col = col;
        open_row = row;
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
            if (i != row) {
                ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
                ui->tableWidget->item(i, 1)->setCheckState(Qt::Unchecked);
            } else {
                ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
            }
        }
        btn_openfile->setEnabled(1);
    } else {
        btn_openfile->setEnabled(0);
    }
}

void FuncWindow::shotsign() {
    emit sendsignal();
}

void FuncWindow::close_window() {
    this->close();
}

void FuncWindow::on_pushButton_6_clicked() {
    QString str = ui->tableWidget->item(open_row, open_col)->text();
    // QProcess方式

    QDir dir(str); // qstring_fileDir  文件路径

    QString FileShellCommand =
        dir.absoluteFilePath(str); // qstring_filename 文件名

    FileShellCommand.replace("/", "\\"); // win32下替换斜杠

    QProcess process;
    process.startDetached(
        "explorer",
        QStringList() << QString("/select,")
                      << QString("%1").arg(FileShellCommand));
    process.waitForFinished();
}
