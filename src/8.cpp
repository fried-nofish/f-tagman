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
	std::map<tag, std::vector<file>>::iterator it;
	for(it=FILE.begin();it!=FILE.end();it++){
		if(it->first.name==labal){
			std::cout<<"当前标签的简介是"<<it->first.explain<<std::endl;
			std::vector<file>result = it->second;
			for (int i = 0; i < result.size(); i++) {
				std::cout << result[i].getname() << std::endl;
			}
			std::cout<<"是否有你需要改名的文件，无请输入1，有则输入其他数字"<<std::endl;
			int op;
			std::cin>>op;
			if(op==1)continue;
			else{
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
				newfile.tagtype = oldfile.tagtype;

				new_name=old_name;

				old_name=result[x].getip();

				for(auto it:FILE){
					for(int i=0;i<it.second.size();i++){
						
						if((it.second[i].getip()==oldfile.getip())&&(it.second[i].getname()==oldfile.getname())){
							
							FILE[it.first].erase(FILE[it.first].begin()+i);
							FILE[it.first].push_back(newfile);
							break;
						}
					}
				}//遍历所有标签寻找是否有需要被改名的文件
		
				if (!rename(old_name.c_str(), new_name.c_str())){
					std::cout<<"rename success"<<std::endl;	
				}
				else {
					std::cout<<"rename error"<<std::endl;
				}
			}
		}
	}
	return;
}