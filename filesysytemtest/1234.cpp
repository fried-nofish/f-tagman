#pragma once
#include"file.h"

using std::cout;
using std::cin;
using std::endl;



void function_02(std::map < tag, std::vector<file> >&FILE)
{
	
	address fileaddress;
	cout << "请输入文件路径: ";
	cin >> fileaddress;
	function_01(fileaddress);
	while (1) {
		if (getout())break;
		string tipname;
		string filename;
		tag tip;
		std::vector<file> document;
		cout << "分别输入文件名和标签名，用空格隔开" << endl;
		cin >> filename;
		cin >> tipname;
		tip.name = tipname;
		file newfile(filename, fileaddress + "//" + filename);
		if (FILE.find(tip) == FILE.end())  //标签名不存在，添加标签操作合法，则存入map中
		{
			document.push_back(newfile);
			FILE.insert(make_pair(tip, document));
			cout << "添加成功" << endl;
		}
		else			//如果标签已存在，由用户选择使用其他标签名还是给标签添加说明
		{
			cout << "已存在 " << tip.name << " 标签" << endl;
			cout << "如需要使用其他标签请输入1，如需要给标签添加说明请输入2" << endl;
			int select;
			cin >> select;
			if (select == 1)continue;
			else if (select == 2)//先给已存在的标签修改说明，再给新增加的标签修改说明
			{
				std::vector<file>newfile;
				newfile = FILE[tip];
				FILE.erase(FILE.find(tip));

			}
			else
			{
				cout << "没有这个选项！！！";
				continue;
			}
		}
	}
}