#include"file.h"

using std::string;

void function_08(const std::map < tag, std::vector<file> > FILE) {
	string old_name;
	string new_name;
	string labal;
	tag tip;
	std::cout << "请输入你需要查找的标签" << std::endl;
	std::cin >> labal;
    tip.name = labal;
	if (FILE.find(tip) != FILE.end()) {
		auto it = FILE.find(tip);
		std::vector<file>result = it->second;
		for (int i = 0; i < result.size(); i++) {
			std::cout << result[i].getname() << std::endl;
		}

		std::cout << "请输入旧文件的路径" << std::endl;
		std::cin >> old_name;
		std::cout << "请输入新文件的路径" << std::endl;
		std::cin >> new_name;

		if (!rename(old_name.c_str(), new_name.c_str())){
			std::cout<<"rename success"<<std::endl;	
		}
		else {
			std::cout<<"rename error"<<std::endl;
		}
	}
	else {

    }
	
	
	return;
}