#include "file.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;

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
    cout << "请输入文件路径: ";
    cin >> fileaddress;
    function_01(fileaddress);
    while (1) {
        if (getout()) break;
        string tipname;
        string filename;
        tag    tip;
        cout << "分别输入文件名和标签名，用空格隔开" << endl;
        cin >> filename;
        cin >> tipname;
        tip.name = tipname;
        file newfile(filename, fileaddress + "//" + filename);
        if (FILE.find(tip)
            == FILE.end()) // 标签名不存在，添加标签操作合法，则存入map中
        {
            std::vector<file> document; // 新的vector<file>储存新文件
            document.push_back(newfile);
            FILE.insert(make_pair(tip, document));
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
                continue;
            case 2:
                tempfile = &FILE[tip];
                FILE.erase(FILE.find(tip));
                cout << "请输入对原标签的说明" << endl;
                cin >> old_tip.explain;
                cout << "请输入对新标签的说明" << endl;
                cin >> tip.explain;
                document.push_back(newfile);
                FILE.insert(make_pair(old_tip, *tempfile));
                FILE.insert(make_pair(tip, document));
                continue;
            case 3:
                FILE[tip].push_back(newfile);
                continue;
            default:
                cout << "没有这个选项！！！" << endl;
                continue;
            }
        }
    }
}
