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
	read(fileaddress);
	while (1) {
		if (getout())break;
		string tipname;
		string filename;
		tag tip;
		std::vector<file> document;
		cin >> filename;
		cin >> tipname;
		tip.name = tipname;
		file newfile(filename, fileaddress + "//" + filename);
		if (FILE.find(tip) == FILE.end())
		{
			document.push_back(newfile);
			FILE.insert(make_pair(tip, document));
			cout << "添加成功" << endl;
		}
		else
		{
			cout << "已存在 " << tip.name << " 标签" << endl;
			cout << "如需要使用其他标签请输入1，如需要给标签添加说明请输入2" << endl;
			int select;
			cin >> select;
			if (select == 1)continue;
			else
			{

				FILE[tip];
			}
		}
	}
}