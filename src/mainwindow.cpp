#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "funcwindow.h"
#include "api.h"

#include <QImageReader>
#include <QFile>
#include <QPushButton>
#include <QLabel>
#include <windows.h>

inline QSize getPreferredImageSize(const QString &fileName, int w) {
    QImageReader ir(fileName);
    return ir.size() * (w * 1. / ir.size().width());
}

QString MainWindow::dbPath() const {
    return QApplication::applicationDirPath().append("/test.txt");
}

void MainWindow::loadData() {
    QFile file(dbPath());
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.isOpen()) {
        qDebug() << file.errorString();
        return;
    }

    QDataStream in(&file);
    QString     str = file.readLine();
    str             = str.trimmed();
    int file_num    = str.toInt();
    while (file_num--) {
        int     tag_num;
        QString file_name = file.readLine();
        file_name         = file_name.trimmed();
        str               = file.readLine();
        str               = str.trimmed();
        tag_num           = str.toInt();
        while (tag_num--) {
            QString tag_name    = file.readLine();
            tag_name            = tag_name.trimmed();
            QString tag_explain = file.readLine();
            tag_explain         = tag_explain.trimmed();

            string                newfile_path = file_name.toStdString();
            std::filesystem::path newfile(newfile_path);
            string                newfile_name = newfile.filename().string();

            fileaddtag(
                fileinset(newfile_name, newfile_path),
                taginvec(tag_name.toStdString(), tag_explain.toStdString()));
        }
    }

    file.close();
}

void MainWindow::storeData() {
    QFile file(dbPath());
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);

    if (!file.isOpen()) {
        qDebug() << file.errorString();
        return;
    }

    QTextStream       out(&file);
    std::vector<File> a_file = showallfile();
    out << a_file.size() << "\n";
    for (auto &it : a_file) {
        out << QString::fromStdString(it.address + "\n");
        std::vector<Tag> taglist;
        taglist = fileshowtag(it);
        out << taglist.size() << "\n";
        for (auto &itr : taglist) {
            out << QString::fromStdString(itr.name + "\n");
            out << QString::fromStdString(itr.explain + "\n");
        }
    }

    file.close();
}

void MainWindow::initialize() {
    setWindowIcon(QIcon(":/img/logo.jpg"));
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(getPreferredImageSize(":/img/start_interface.jpg", 1000));
    setStyleSheet("QMainWindow {border-image:url(:/img/start_interface.jpg)}");

    // 立即开始
    auto btn_start = new QPushButton(this);
    btn_start->move(495, 435);
    btn_start->setFixedSize(
        getPreferredImageSize(":/img/startbutton.png", 250));
    btn_start->setStyleSheet("border-image:url(:/img/startbutton.png);");
    connect(btn_start, SIGNAL(clicked()), this, SLOT(enterfunc()));

    // 关闭窗口
    auto btn_close = new QPushButton(this);
    btn_close->move(960, 15);
    btn_close->setFixedSize(23, 23);
    btn_close->setStyleSheet("border-image:url(:/img/close.png);");
    connect(btn_close, SIGNAL(clicked()), this, SLOT(close()));

    // 最小化
    auto btn_off_screen = new QPushButton(this);
    btn_off_screen->move(920, 15);
    btn_off_screen->setFixedSize(23, 23);
    btn_off_screen->setStyleSheet("border-image:url(:/img/off_screen.png);");
    connect(btn_off_screen, SIGNAL(clicked()), this, SLOT(showMinimized()));

    // 更多选项菜单栏
    auto act_settings = new QAction(QIcon(":/img/config.png"), tr("设置"));
    auto act_report = new QAction(QIcon(":/img/advice.png"), tr("意见反馈"));
    auto act_aboutus = new QAction(QIcon(":/img/about_us.png"), tr("关于我们"));

    auto menu = new QMenu(this);
    menu->addAction(act_settings);
    menu->addSeparator();
    menu->addAction(act_report);
    menu->addSeparator();
    menu->addAction(act_aboutus);

    // 更多选项
    auto btn_more = new QPushButton(this);
    btn_more->move(880, 15);
    btn_more->setFixedSize(23, 23);
    btn_more->setStyleSheet("border-image:url(:/img/hamburger_button.png);");
    btn_more->setMenu(menu);

    // 主题
    auto btn_theme = new QPushButton(this);
    btn_theme->move(840, 15);
    btn_theme->setFixedSize(23, 23);
    btn_theme->setStyleSheet("border-image:url(:/img/theme.png);");

    // 主页面文字 - 1
    auto label1 = new QLabel(this);
    label1->setText(tr("深度管理，轻松找到"));
    label1->setGeometry(400, 230, 700, 100);
    label1->setStyleSheet("color:rgb(0, 122, 255)");
    label1->setFont(QFont("微软雅黑", 45, 10));

    // 主页面文字 - 2
    auto label2 = new QLabel(this);
    label2->setText(tr("如果你也觉得本系统好用的话，那我觉得这件事，泰裤辣！"));
    label2->setGeometry(400, 310, 700, 100);
    label2->setStyleSheet("color:rgb(117, 117, 209)");
    label2->setFont(QFont("微软雅黑", 15, 0));

    // 主页面文字 - 标题
    auto label3 = new QLabel(this);
    label3->setText(tr("文件标签管理系统"));
    label3->setGeometry(30, -5, 300, 50);
    label3->setStyleSheet("color:rgb(255, 255, 255)");
    label3->setFont(QFont("微软雅黑", 12, 0));

    // LOGO
    auto label4 = new QLabel(this);
    label4->setGeometry(0, 5, 30, 30);
    label4->setStyleSheet("border-image:url(:/img/logo.jpg);");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    loadData();
    initialize();
}

MainWindow::~MainWindow() {
    delete ui;
    storeData();
}

bool MainWindow::nativeEvent(
    const QByteArray &eventType, void *message, qintptr *result) {
    const auto msg = static_cast<MSG *>(message);
    if (msg->message == WM_NCHITTEST) {
        const auto pos = QCursor::pos(screen()) - frameGeometry().topLeft();
        if (qobject_cast<QPushButton *>(childAt(pos)) == nullptr) {
            *result = HTCAPTION;
            return true;
        }
    }
    return false;
}

void MainWindow::enterfunc() {
    hide();
    FuncWindow *con = new FuncWindow;
    connect(con, SIGNAL(sendsignal()), this, SLOT(show()));
    con->show();
}
