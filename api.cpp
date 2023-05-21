
#include "api.h"
#include <filesystem>
namespace fs = std::filesystem;

// 用于储存，增删用函数实现以和 View 同步
std::set<File> FileList;
std::vector<Tag> TagList;
std::queue<int>TagScript;

std::vector<Tag> fileshowtag(const File& file)
{
    string filepath = file.address + file.name;
    std::vector<Tag> tag;
    for(auto &it : TagList){
        for(auto &it2 : it.T_filelist){
            string cur = it2->address + it2->name;
            if(cur == filepath){
                tag.push_back(it);
                break;
            }
        }
    }
    return tag; 
}  //展示单文件标签

bool fileindir(File file)
{
    string s = file.address + file.name;
    if (fs::exists(s) && fs::is_directory(s))
    {
        return true;
    }
    return false;
}  //确认输入文件存在于目录下


Tagint taginvec(string name, string explain)
{
    //先查找，存在tag则返回其下标
	for(int i = 0; i < TagList.size(); ++i)
	{
		if(TagList[i].name==name && TagList[i].explain==explain) return i;
	}
    //不存在tag则构建一个
    Tag newtag(name,explain);
    if(!TagScript.empty()){
        TagList[TagScript.front()] = newtag;
        TagScript.pop();
    }
    else{
        TagList.push_back(newtag);
    }
    return TagList.size();
}  //确认输入tag存在于vector中,存在则返回其下标，不存在则创建并返回新的size

File* fileinset(string name, string addr)
{
    File newfile(name,addr);
    FileList.insert(newfile);
    auto itr = FileList.find(newfile);
    File* it = &(File)*itr;
    return it;
}  //确认输入文件存在于set中，用于给文件加标签

std::pair<File*,Tagint> fileinvec(string filename, string addr,string tagname, string explain)
{

    for(int i = 0; i < TagList.size(); ++i)
	{
		for(int j = 0; j < TagList[i].T_filelist.size();++j)
        {
            if(TagList[i].T_filelist[j]->name==filename&&TagList[i].T_filelist[j]->address==addr
            &&TagList[i].name==tagname&&TagList[i].explain==explain)
            return std::pair<File*,Tagint>(TagList[i].T_filelist[j],j);
        }
        return std::pair<File*,Tagint>(NULL,NULL);
	}
}  //确认输入文件存在于vector中，用于删标签

bool fileaddtag(File* file, Tagint size)
{
    if(size==TagList.size())--size;
    TagList[size].T_filelist.push_back(file);
    return 1;
}  //给文件添加标签

bool filedeltag(File* file, Tagint tagpoint)
{
    for(int i = 0; i < TagList[tagpoint].T_filelist.size(); i++)
    {
        //如果此标签里有此文件，删除并返回1，否则返回0
        if(TagList[tagpoint].T_filelist[i]->name == file->name && TagList[tagpoint].T_filelist[i]->address == file->address)
        {
            TagList[tagpoint].T_filelist.erase(TagList[tagpoint].T_filelist.begin() + i);
            return 1;
        }
    }
    return 0;
}  //给文件删除标签

bool tagdel(string name, string explain)
{
    for(int i = 0 ; i < TagList.size() ; i ++)
    {
        if(TagList[i].name == name && TagList[i].explain == explain) 
        {
            TagList[i].name = "", TagList[i].explain = "";
            TagScript.push(i);
            return 1;
        }
    }
    return 0;
}  //删除某标签

bool tagrename(string old_name, string new_name, string explain)
{
    for(int i = 0; i < TagList.size(); i++)
    {
        if(TagList[i].name == old_name && TagList[i].explain == explain)
        {
            TagList[i].name = new_name;
            return 1;
        }
    }
    return 0;
} //标签改名

bool tagexplain(string name, string old_explain, string new_explain)
{
    for(int i = 0; i < TagList.size(); i++)
    {
        if(TagList[i].name == name && TagList[i].explain == old_explain)
        {
            TagList[i].explain = new_explain;
            return 1;
        }
    }
    return 0;
}  //给标签添加说明
