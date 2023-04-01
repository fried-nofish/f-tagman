#include"file.h"
//用于实现file类中的方法

file file::operator=(const file& f)
{
	file newfile("0","0");
	newfile.id = f.id;
	newfile.name = f.name;
	return newfile;
}