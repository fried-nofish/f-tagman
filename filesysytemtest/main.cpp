#include"file.h"



using std::cin;
using std::cout;

int main()
{
	std::map<tag, std::vector<file> >FILE;
	address filepath;
	while (1)
	{
		menu();
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "输入要管理的目录名: ";
			cin >> filepath;
			read(filepath);
			break;
		case 2:
			function_02(FILE);
			break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7:break;
		case 8:break;
		default:
			cout<<"你故意找茬是吧？";
			system("pause");
			break;
		}

	}

}