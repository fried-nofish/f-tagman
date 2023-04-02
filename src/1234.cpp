#include "file.h"

#include <filesystem>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::make_pair;

namespace fs = std::filesystem;

bool function_01(address filepath) {
    fs::path str(filepath);
    if (!fs::exists(str)) // 必须先检测目录是否存在才能使用文件入口.
        return 1;
    fs::directory_entry entry(str); // 文件入口
    if (entry.status().type()
        == fs::file_type::directory) // 这里用了C++11的强枚举类型
        cout << "该路径是一个目录" << endl;
    fs::directory_iterator list(str); // 文件入口容器
    for (auto& it : list)
        cout
            << it.path().filename()
            << endl; // 通过文件入口（it）获取path对象，再得到path对象的文件名，将之输出
    system("pause");
    return 0;
}

void function_02(std::map<tag, std::vector<file>>& FILE) {
    address fileaddress;
    cout << "请输入文件父目录: ";
    cin >> fileaddress;
    function_01(fileaddress);
    while (1) {
        if (getout()) break;
        string tipname;  //用户的标签名
        string filename;  //用户的文件名
        tag    tip;
        cout << "分别输入文件名和标签名，用空格隔开" << endl;
        cin >> filename;
        cin >> tipname;
        tip.name = tipname;
        file newfile(filename, fileaddress + "//" + filename);
        if (FILE.find(tip)== FILE.end()) // 标签名不存在，添加标签操作合法，则存入map中
        {
            std::vector<file> document; // 新的vector<file>储存新文件
            document.push_back(newfile);
            FILE.insert(make_pair(tip, document));
            newfile.tagtype.insert(make_pair(tip,1)); //在文件中存储该标签
            
            cout << "添加成功" << endl;
        }
       
        else // 如果标签已存在，由用户选择使用其他标签名还是给标签添加说明
        {
            cout << "已存在 " << tip.name << " 标签" << endl;
            cout << "如需要使用其他标签请输入1，如需要给该标签添加说明请输入2，"
                "如直接添加该标签请输入3"
                << endl;
            tag old_tip;
            old_tip.name = tip.name; // 如果用户需要修改标签说明，删除旧标签，将原value存至此标签对应处
            std::vector<file>* tempfile; // 如果用户需要修改标签说明，临时储存value值
            std::vector<file>document; // 如果用户需要修改标签说明，创建新的vector<file>储存新文件
            int select;
            cin >> select;
            switch (select) {
                case 1:
                    while(tip.name==old_tip.name)
                    {   
                        cout<<"请输入新的标签名: "<<endl;
                        if(tip.name!=old_tip.name)
                        {
                        cin >> tip.name;
                        newfile.tagtype.insert(make_pair(tip,1));
                        }
                        else 
                        {
                        cout<<"请输入与原来不同的标签名！！！"<<endl;
                        if(getout())break;
                        }
                    }
                    continue;
                case 2:
                    tempfile = &FILE[tip];
                    FILE.erase(FILE.find(tip));
                    for (auto pair : *tempfile)                //在文件中移除旧的注释
                    {
                        pair.tagtype.erase(old_tip);
                    }
                    cout << "请输入对原标签的说明" << endl;
                    cin >> old_tip.explain;
                    cout << "请输入对新标签的说明" << endl;
                    cin >> tip.explain;
                    document.push_back(newfile);
                    FILE.insert(make_pair(old_tip, *tempfile));//在增加注释的标签下重新存放文件
                    FILE.insert(make_pair(tip, document));
                    for (auto pair : *tempfile)                //在文件中存入新的注释
                    {
                        pair.tagtype.insert(make_pair(old_tip,1));
                    }
                    newfile.tagtype.insert(make_pair(tip,1));
                    continue;
                case 3:
                    FILE[tip].push_back(newfile);
                    newfile.tagtype.insert(make_pair(tip,1));
                    continue;
                default:
                    cout << "没有这个选项！！！" << endl;
                    continue;
            }
        }
    }
}

void function_03(std::map<tag, std::vector<file>>& FILE)
{
    string filename;
    address fileip;
    cout<<"请输入需要删除文件的父目录"<<endl;
    cin>>fileip;
    function_01(fileip);
    cout<<"请输入需要删除的文件"<<endl;
    cin>>filename;
    fileip=fileip+"//"+filename;
    file delete_file(filename,fileip);
    cout<<"该文件的标签有: "<<endl;

    for(auto it:FILE)
    {
		for(int i=0;i<it.second.size();i++)
        {	
			if((it.second[i].getip()==delete_file.getip())&&(it.second[i].getname()==delete_file.getname()))
            {		
				cout<<it.first.name<<endl;
                cout<<it.first.explain<<endl;
				break;
			}
		}
	}

    tag tip;
    cout<<"分别输入你需要删除的标签名和说明: "<<endl;
    cin>>tip.name;
    cin>>tip.explain;
    for(int i=0;i<FILE[tip].size();i++){
        if((FILE[tip][i].getip()==delete_file.getip())&&(FILE[tip][i].getname()==delete_file.getname())){
			FILE[tip][i].tagtype.erase(tip);
            FILE[tip].erase(FILE[tip].begin()+i);
            if(FILE[tip].empty())FILE.erase(tip);
			break;
		}
    }
}

void function_04(std::map<tag, std::vector<file>>& FILE)
{
    string filename;
    address fileip;
    cout<<"请输入需要修改文件的父目录: "<<endl;
    cin>>fileip;
    function_01(fileip);
    cout<<"请输入文件名: "<<endl;
    cin>>filename;
    fileip=fileip+"//"+filename;
    file change_file(filename,fileip);
    cout<<"该文件的标签有: "<<endl;

    for(auto it:FILE)
    {
		for(int i=0;i<it.second.size();i++)
        {	
			if((it.second[i].getip()==change_file.getip())&&(it.second[i].getname()==change_file.getname()))
            {		
				cout<<it.first.name;
                cout<<it.first.explain<<endl;
				break;
			}
		}
	}
    tag tip;
    tag newtip;
    cout<<"输入你需要修改的标签名和说明: "<<endl;
    cin >> tip.name;
    cin >> tip.explain;
    cout<<"你要修改的是： "<<endl;
    cout<< fileip <<endl;
    cout<< tip.name <<"      "<< tip.explain <<endl;
    cout<<"你要修改原标签名为：";
    cin >> newtip.name;
    cout<<"你要修改原标签说明为：";
    cin >> newtip.explain;
        for(int i=0;i<FILE[tip].size();i++){
        if((FILE[tip][i].getip()==change_file.getip())&&(FILE[tip][i].getname()==change_file.getname()))
        {
			FILE[tip][i].tagtype.erase(tip);
            FILE[tip][i].tagtype.insert(make_pair(newtip,1));
			break;
		}
    }
}