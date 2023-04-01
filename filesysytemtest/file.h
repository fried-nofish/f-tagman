#pragma once
#include<iostream>
#include<filesystem>
#include<map>
#include<vector>

using std::string;
namespace fs = std::filesystem;
typedef string address;

class file
{
private:
	string id;//地址
	string name;//文件名
public:
	file(string id,string name)
	{
		this->name = name;
		this->id = id;
	}
};

struct tag
{
	string name;
	string explain = "0";
	bool operator<(const tag& a)const {   
		return name == a.name ? explain < a.explain : name < a.name ;
	}
};

bool read(address filepath);
void menu();
void function_02(std::map < tag, std::vector<file> >& FILE);
bool getout()