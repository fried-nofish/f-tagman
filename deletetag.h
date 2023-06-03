#ifndef DELETETAG_H
#define DELETETAG_H

#include <QWidget>
#include <QString>
#include "api.h"

namespace Ui {
class DeleteTag;
}

class DeleteTag : public QWidget
{
    Q_OBJECT

public:

    int num;
    explicit DeleteTag(QWidget *parent = nullptr);
    ~DeleteTag();
    void init(std::vector<Tag>);

private slots:
    void on_pushButton_clicked();


    void on_comboBox_activated(int index);

private:
    Ui::DeleteTag *ui;
};

#endif // DELETETAG_H
