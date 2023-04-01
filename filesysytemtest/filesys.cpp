#pragma once
#include"file.h"

using std::cout;
using std::cin;
using std::endl;

bool function_01(address filepath)
{
	fs::path str(filepath);
	if (!fs::exists(str))		//必须先检测目录是否存在才能使用文件入口.
		return 1;
	fs::directory_entry entry(str);		//文件入口
	if (entry.status().type() == fs::file_type::directory)	//这里用了C++11的强枚举类型
		cout << "该路径是一个目录" << endl;
	fs::directory_iterator list(str);	        //文件入口容器
	for (auto& it : list)
		cout << it.path().filename() << endl;	//通过文件入口（it）获取path对象，再得到path对象的文件名，将之输出
	system("pause");
	return 0;
}

void menu()
{
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

bool getout()
{
	int select;
	cout << "如需结束程序请输入 1 ，否则输入任意数字";
	cin >> select;
	return select == 1;
}
