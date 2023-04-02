#include "file.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
    cout << "********** 9.显示一个文件的所有标签 **********" << endl;
    cout << "********** 请输入你需要使用的功能：**********" << endl;
}

bool getout() {
    int select;
    cout << "如需结束程序请输入 1 ，否则输入任意数字： ";
    cin >> select;
    return select == 1;
}


string judge_multi(string name, std::map < tag, std::vector<file> >& FILE) {
	//检测此标签是否有多种类型
	//如有 则展示多种类型并输入某种
	tag tip;
	tip.name = name, tip.explain = "0";
	int cnt = 0;
	for (auto it = FILE.find(tip); it != FILE.end(); it++) {
		if (it->first.name != name) continue;
		//cout << "!!!";
		cnt++;
		if (cnt == 2) {
			cout << "此标签有多种类型：" << "\n";
			it--;
			cout << it->first.explain << " ";
			it++;
		}
		if (cnt >= 2) {
			cout << it->first.explain << " ";
		}
	}
	std::string secname = "0";
	if (cnt == 0) return "null";
	if (cnt == 1) return secname;
	cout << "请选择此标签的类型 : " << "\n";
	cin >> secname;
	return secname;
}
