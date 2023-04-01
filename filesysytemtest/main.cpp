#include"file.h"



using std::cin;
using std::cout;

int main()
{
	std::map<tag, std::vector<file> >FILE;

	menu();
	int select;
	cin >> select;
	switch(select)
	{
	case 1:
		function_01(FILE); 
		break;
	case 2:break;
	case 3:break;
	case 4:break;
	case 5:break;
	case 6:break;
	case 7:break;
	case 8:
		function_08();
		break;
	default:
		break;
	}

}