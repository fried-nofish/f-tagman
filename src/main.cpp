#include "file.h"

using std::cin;
using std::cout;

int main(int argc, char *argv[]) {
    //! TODO: handle application startup here

    std::map<tag, std::vector<file>> FILE;
    address filepath;
    while (1) {
        menu();
        int select;
        cin >> select;
        switch (select) {
            case 1:
                cout << "输入要管理的目录名: "<<std::endl;
                cin >> filepath;
                function_01(filepath);
                break;
            case 2:
                function_02(FILE);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                function_08(FILE);
                break;
            default:
                cout << "你故意找茬是吧？";
                system("pause");
                break;
        }
    }

    return 0;
}
