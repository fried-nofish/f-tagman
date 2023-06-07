#include "funcwindow.h"
#include "qpushbutton.h"
#include "ui_funcwindow.h"
#include "utils.h"
#include "api.h"
#include "dialog.h"

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

FuncWindow::FuncWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FuncWindow) {
    initialize();
}

FuncWindow::~FuncWindow() {
    delete ui;
}

void FuncWindow::initialize() {
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/img/logo.jpg"));
    setFixedSize(getPreferredImageSize(":/img/start_interface.jpg", 1000));
    setStyleSheet("QMainWindow {border-image:url(:/img/fun_interface.jpg)}");

    setupUi();
    initializeButtons();

    //! initialize table widget
    auto vScrollBar = ui->tableWidget->verticalScrollBar();
    if (vScrollBar != nullptr) {
        vScrollBar->setValue(ui->tableWidget->verticalScrollBar()->maximum());
    }
    connect(
        ui->tableWidget,
        &QTableWidget::cellChanged,
        this,
        &FuncWindow::updateCheckState);
}

void FuncWindow::setupUi() {
    // 关闭窗口按钮
    auto btn_close =
        addButton(QPoint(950, 15), QSize(25, 25), ":/img/close.png");
    connect(btn_close, &QPushButton::clicked, this, &FuncWindow::close);
    connect(btn_close, &QPushButton::clicked, this, &FuncWindow::closed);

    // 缩小窗口按钮
    connect(
        addButton(QPoint(920, 15), QSize(23, 23), ":/img/off_screen.png"),
        &QPushButton::clicked,
        this,
        &FuncWindow::showMinimized);

    //! 加按钮的菜单栏
    auto act_settings = new QAction(QIcon(":/img/config.png"), tr("设置"));
    auto act_report = new QAction(QIcon(":/img/advice.png"), tr("意见反馈"));
    auto act_aboutus = new QAction(QIcon(":/img/about_us.png"), tr("关于我们"));
    auto menu = new QMenu(this);
    menu->addAction(act_settings);
    menu->addSeparator();
    menu->addAction(act_report);
    menu->addSeparator();
    menu->addAction(act_aboutus);

    //! 更多窗口按钮
    addButton(QPoint(880, 15), QSize(23, 23), ":/img/hamburger_button.png")
        ->setMenu(menu);

    //! 主题窗口按钮
    addButton(QPoint(840, 15), QSize(23, 23), ":/img/theme.png");

    //! 窗口标题
    auto label3 = new QLabel(this);
    label3->setText(tr("文件标签管理系统"));
    label3->setGeometry(30, -5, 300, 50);
    label3->setStyleSheet("color:rgb(255, 255, 255)");
    label3->setFont(QFont("微软雅黑", 12, 0));

    //! 左上角 logo
    auto label4 = new QLabel(this);
    label4->setGeometry(0, 5, 30, 30);
    label4->setStyleSheet("border-image:url(:/img/logo.jpg);");
}

void FuncWindow::initializeButtons() {
    struct value_type {
        QPushButton *button;
        QPoint       pos;
        int          width;
        QString      imageUrl;
        void (FuncWindow::*slot)();
    };

    btn_openfile = new QPushButton(this);
    btn_openfile->setEnabled(false);

    QList<value_type> buttons{
        {new QPushButton(this),
         QPoint(80,  80),
         101, ":/img/addtag.png",
         &FuncWindow::addTag     },
        {new QPushButton(this),
         QPoint(260, 80),
         105, ":/img/deltag.png",
         &FuncWindow::removeTag  },
        {new QPushButton(this),
         QPoint(440, 80),
         110, ":/img/viewtag.png",
         &FuncWindow::displayTags},
        {new QPushButton(this),
         QPoint(620, 80),
         108, ":/img/findfile.png",
         &FuncWindow::findFile   },
        {new QPushButton(this),
         QPoint(800, 80),
         107, ":/img/renametag.png",
         &FuncWindow::renameTag  },
        {new QPushButton(this),
         QPoint(840, 400),
         107, ":/img/explain.png",
         &FuncWindow::explain    },
        {btn_openfile,
         QPoint(840, 220),
         107, ":/img/turn_on.png",
         &FuncWindow::openFile   },
    };

    for (auto &[button, p, w, url, slot] : buttons) {
        const auto size = getPreferredImageSize(url, w);
        button->move(p);
        button->setFixedSize(size);
        button->setStyleSheet(QStringLiteral("border-image:url(%1);").arg(url));
        connect(button, &QPushButton::clicked, this, slot);
    }
}

QPushButton *
    FuncWindow::addButton(QPoint p, QSize size, const QString &imageUrl) {
    auto button = new QPushButton(this);
    button->move(p);
    button->setFixedSize(size);
    button->setStyleSheet(
        QStringLiteral("border-image:url(%1);").arg(imageUrl));
    return button;
}

void FuncWindow::findFile() {
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

void FuncWindow::displayTags() {
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

void FuncWindow::addTag() {
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
            this,
            tr("QInputdialog_Name"),
            tr("标签名"),
            QLineEdit::Normal,
            "",
            &bOk);
        if (bOk)
            fileaddtag(
                fileinset(newfile_name, newfile_path),
                taginvec(sName.toStdString(), ""));
    }
}

void FuncWindow::removeTag() {
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
            QMessageBox::information(this, tr("警告"), tr("当前文件没有标签"));
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

void FuncWindow::renameTag() {
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
            tr("QInputdialog_Name"),
            tr("更改的标签名"),
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

void FuncWindow::updateCheckState(int row, int col) {
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

void FuncWindow::explain() {}

void FuncWindow::openFile() {
    QString path = ui->tableWidget->item(open_row, open_col)->text();
    path         = QDir(path).absolutePath();

#ifdef Q_OS_WIN
    path.replace("/", "\\"); // win32下替换斜杠
#endif

    QProcess process;
    process.startDetached("explorer", QStringList() << "/select," << path);
    process.waitForFinished();
}
