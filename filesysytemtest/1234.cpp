#pragma once
#include"file.h"

using std::cout;
using std::cin;
using std::endl;


void function_01(std::map < tag, std::vector<file> >&FILE)
{
	
	address fileaddress;
	cin >> fileaddress;//输入要管理的目录名
	read(fileaddress);
	while (1) {
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
		}
		else
		{

		}
	}
}