#include"file.h"

using std::string;
namespace fs = std::filesystem;

void function_08(std::map < tag, std::vector<file> > &FILE) {
	string old_name;
	string new_name;
	string labal;
	string shuoming;
	tag tip;
	std::cout << "请输入你需要查找的标签" << std::endl;
	std::cin >> labal;
	// std::cout<<"请输入你需要查找的标签的简介"<<std::endl;
	// std::cin>>shuoming;
    tip.name = labal;
	// tip.explain=shuoming;

	if (FILE.find(tip) != FILE.end()) {
		auto it = FILE.find(tip);
		std::vector<file>result = it->second;
		
		
		for (int i = 0; i < result.size(); i++) {
			std::cout << result[i].getname() << std::endl;
		}

		int x=-1;

		std::cout << "请输入旧文件的名称" << std::endl;
		std::cin >> old_name;

		for (int i = 0; i < result.size(); i++) {
			if(result[i].getname()==old_name)x=i;
		}

		if(x==-1){
			std::cout<<"没有找到相应文件"<<std::endl;
			return;
		}

		old_name=result[x].getip();
		file oldfile=result[x];

		fs::path father(old_name);
		
		old_name=(father.parent_path().u8string());
		
		std::cout << "请输入新文件的名称" << std::endl;
		std::cin >> new_name;
		
		old_name=old_name+"//"+new_name;

		file newfile(new_name,old_name);

		new_name=old_name;

		old_name=result[x].getip();

		for(auto it:FILE){
			for(int i=0;i<it.second.size();i++){
				// std::cout<<it.second[i].getip()<<" "<<oldfile.getip()<<std::endl;
				// std::cout<<it.second[i].getname()<<" "<<oldfile.getname()<<std::endl;
				if((it.second[i].getip()==oldfile.getip())&&(it.second[i].getname()==oldfile.getname())){
					// std::cout<<1<<std::endl;
					FILE[it.first].erase(FILE[it.first].begin()+i);
					FILE[it.first].push_back(newfile);
					break;
				}
			}
		}//遍历所有标签寻找是否有需要被改名的文件

		// FILE[tip].erase(FILE[tip].begin()+x);
		// FILE[tip].push_back(newfile);//删除旧文件增加新文件

		
		if (!rename(old_name.c_str(), new_name.c_str())){
			std::cout<<"rename success"<<std::endl;	
		}
		else {
			std::cout<<"rename error"<<std::endl;
		}
	}
	else {
		std::cout<<"不存在该标签"<<std::endl;
    }
	
	
	return;
}