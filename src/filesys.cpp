#pragma once
#include "file.h"

using std::cin;
using std::cout;
using std::endl;

void menu() {
    cout << "********** 欢迎来到文件标签管理系统！！！**********" << endl;
    cout << "********** 1.展示子目录 **********" << endl;
    cout << "********** 2.给文件添加标签 **********" << endl;
    cout << "********** 3.给文件删除标签 **********" << endl;
    cout << "********** 4.给文件修改标签 **********" << endl;
    cout << "********** 5.移除标签 **********" << endl;
    cout << "********** 6.更改标签名称 **********" << endl;
    cout << "********** 7.查询标签下所有文件 **********" << endl;
    cout << "********** 8.修改指定文件的文件名 **********" << endl;
    cout << "********** 请输入你需要使用的功能：**********" << endl;
}

bool getout() {
    int select;
    cout << "如需结束程序请输入 1 ，否则输入任意数字： ";
    cin >> select;
    return select == 1;
}
