#include"file.h"

void function_08() {
	string old_name;
	string new_name;
	std::cout << "��������ļ���·��" << std::endl;
	std::cin >> old_name;
	std::cout << "���������ļ���·��" << std::endl;
	std::cin >> new_name;
	if (!rename(old_name.c_str(), new_name.c_str())){
		std::cout<<"rename success"<<std::endl;	
	}
	else {
		std::cout<<"rename error"<<std::endl;
	}
	return;
}