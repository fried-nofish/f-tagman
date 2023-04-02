#include"file.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::make_pair;

//打印现有所有标签
void printtag(std::map < tag, std::vector<file> >& FILE)
{
	//用户选择是否展示现有所有标签
	int choice;
	cout << "******是否展示现有所有标签？******" << endl;
	cout << "******      0.不展示        ******" << endl;
	cout << "******      1.展示          ******" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "***标签名称***" << "             " << "***标签简介***" << endl;
		std::map<tag, std::vector<file>>::iterator it;
		for (it = FILE.begin(); it != FILE.end(); it++)
		{
			cout << "   " << it->first.name << "               " << it->first.explain << endl;
		}
	}
}

void changeexit_tag(std::map < tag, std::vector<file> >& FILE, tag modify_tip, std::map<tag, std::vector<file>>::iterator re, string name, std::vector<file> before_file)
{
	//查找是否已经存在修改后的标签名称并展示出来
		int count = 0;
		std::map<tag, std::vector<file>>::iterator it;
		for (it = FILE.begin(); it != FILE.end(); it++)
		{
			if (it->first.name == modify_tip.name)
			{
				cout << it->first.name << "         " << it->first.explain << endl;
				count++;
			}
		}
		//如果没有，直接删除原来的标签并插入新标签
		if (count == 0)
		{
			cout << "******确定将标签" << name << "修改为" << modify_tip.name << "吗？******" << endl;
			cout << "******      1.修改        ******" << endl;
			cout << "******      2.不修改      ******" << endl;
			int choice_delete;
			cin >> choice_delete;
			if (choice_delete == 1)
			{
				FILE.erase(re);
				FILE.insert(make_pair(modify_tip, before_file));
			}
		}
		//如果有，让用户输入修改后标签的新简介
		else
		{
			string explain_after;
			cout << "******请输入修改后的标签的简介：";
			cin >> explain_after;
			modify_tip.explain = explain_after;
			FILE.erase(re);
			FILE.insert(make_pair(modify_tip, before_file));
		}
}

//移除标签
void function_05(std::map < tag, std::vector<file> >& FILE)
{
	printtag(FILE);
	std::vector<file> before_file;
	if(getout())return;
	//用户输入需要删除的标签名称
	cout << "******请输入需要移除的标签名称:";
	string name;
	cin >> name;
	
	tag delete_tip;
	delete_tip.name = name;

	//输出所有符合条件的标签名称及备注
	int count = 0;
	std::map<tag, std::vector<file>>::iterator it;
	for (it = FILE.begin(); it != FILE.end(); it++)
	{
		if (it->first.name == name)
		{
			cout << it->first.name << "         " << it->first.explain << endl;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "******没有找到该标签！******" << endl;
	}
	else if (count == 1)
	{
		cout << "******确定要删除上述标签吗？******" << endl;
		cout << "******      1.删除        ******" << endl;
		cout << "******      2.不删除        ******" << endl;
		int choice_delete;
		cin >> choice_delete;
		if (choice_delete == 1)
		{
			before_file = FILE[delete_tip];
			FILE.erase(delete_tip);
		}
	}
	else
	{
		string explain;
		cout << "******需要删除上述哪个标签？******" << endl;
		cout << "******请输入该标签的简介：";
		cin >> explain;
		delete_tip.explain = explain;
		before_file = FILE[delete_tip];
		FILE.erase(delete_tip);
	}
	if(count != 0)
	{
		std::vector<file>::iterator fi;
		for(fi = before_file.begin(); fi != before_file.end(); fi++)
		{
			(*fi).tagtype[delete_tip] = 0;
		}		
	}

}


//更改标签名称
void function_06(std::map < tag, std::vector<file> >& FILE)
{
	printtag(FILE);
	std::vector<file> before_file;
	if(getout())return;

	//用户输入需要修改的标签名称
	cout << "******请输入需要修改的标签名称：";
	string name;
	cin >> name;
	tag modify_tip, before_tip;
	before_tip.name = name;

	//输出所有符合条件的标签名称及备注
	int count = 0;
	std::map<tag, std::vector<file>>::iterator it;
	std::map<tag, std::vector<file>>::iterator re;
	for (it = FILE.begin(); it != FILE.end(); it++)
	{
		if (it->first.name == name)
		{
			cout << it->first.name << "         " << it->first.explain << endl;
			re = it;
			count++;
		}
	}
	if (count == 0)
	{
		cout << "******没有找到该标签！******" << endl;
	}
	else if (count == 1)
	{
		cout << "******请输入修改后的标签名称：";
		string modify_name;
		cin >> modify_name;
		modify_tip.name = modify_name;
		before_file = re->second;

		changeexit_tag(FILE, modify_tip, re, name, before_file);
	}
	else
	{
		string explain;
		cout << "******需要修改上述哪个标签？******" << endl;
		cout << "******请输入该标签的简介：";
		cin >> explain;
		before_tip.explain = explain;
		re = FILE.find(before_tip);
		before_file = re->second;

		cout << "******请输入修改后的标签名称：";
		string modify_name;
		cin >> modify_name;
		modify_tip.name = modify_name;

		changeexit_tag(FILE, modify_tip, re, name, before_file);
	}
	if(count != 0)
	{
		std::vector<file>::iterator fi;
		for(fi = before_file.begin(); fi != before_file.end(); fi++)
		{
			(*fi).tagtype.erase(before_tip);
			(*fi).tagtype.insert(make_pair(modify_tip,1));
		}
	}

}
