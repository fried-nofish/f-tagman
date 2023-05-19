
#include "api.h"
#include <filesystem>
namespace fs = std::filesystem;

// 用于储存，增删用函数实现以和 View 同步
std::set<File> FileList;
std::vector<Tag> TagList;
std::set<int>TagScript;

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
Tag* taginvec(string name, string explain)
{

}  //确认输入tag存在于vector中
File* fileinvec(string name, string addr)
{

}  //确认输入文件存在于vector中，用于给文件加标签
File* fileinvec(string name)
{

}  //确认输入文件存在于vector中，用于删标签
bool fileaddtag(File* file, Tag* tag)
{

}  //给文件添加标签
bool filedeltag(File* file, Tag* tagpoint)
{

}  //给文件删除标签
bool tagdel(string name, string explain)
{

}  //删除某标签
bool tagrename(string old_name, string new_name, string explain)
{

} //标签改名
bool tagexplain(string name, string explain)
{

}  //给标签添加说明
