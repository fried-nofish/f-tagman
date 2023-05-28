#pragma once

#include<filesystem>
#include<iostream>
#include<utility>
#include<vector>
#include<queue>
#include<set>

using std::string;

typedef string site;
typedef int Tagint;

class File;
struct Tag;

struct File {
    std::string address;
    std::string name;
    File(std::string address,std::string name)
    {
        this->name=name;
        this->address=address;
    }
    bool operator==(const struct File & f)const       //重载<运算符
    {                                                //根据name和address去重
            return this->name == f.name && this->address == f.address;
    }
    bool operator<(const struct File & f)const       //重载<运算符
    {                                                //根据name和address去重
            return this->name == f.name && this->address == f.address;
    }
};
struct Tag {
    std::string name;
    std::string explain = "";
    Tag(std::string name,std::string explain)
    {
        this->name=name;
        this->explain=explain;
    }
    std::vector<File>T_filelist;
    bool operator==(const Tag &T){
        return (this->name == T.name)&&(this->explain == T.explain)&&(this ->T_filelist == T.T_filelist);
    }
};

std::vector<Tag> fileshowtag(const File&);  //展示单文件标签
bool fileindir(File file);  //确认输入文件存在于目录下
Tagint taginvec(string name, string explain);  //确认输入tag存在于vector中
File fileinset(string name, string addr);  //确认输入文件存在于vector中，用于给文件加标签
std::pair<File,Tagint> fileinvec(string name, string addr);  //确认输入文件存在于vector中，用于删标签
bool fileaddtag(File file, Tagint size);  //给文件添加标签
bool filedeltag(File file, Tagint tagpoint);  //给文件删除标签
bool tagdel(string name, string explain);  //删除某标签
bool tagrename(string old_name, string new_name, string explain);  //标签改名
bool tagexplain(string name, string old_explain, string new_explain);  //给标签添加说明


