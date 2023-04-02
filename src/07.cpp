#include"file.h"
using std::cout;
using std::cin;
using std::string;

void function_07(std::map < tag, std::vector<file> >& FILE) {
	cout << "tip: ‘+ filename’表示有此标签的文件 ‘- filename’表示无此标签的文件" << "\n";
	cout << "请输入标签个数及名称：" << "\n";
	int n; cin >> n;
	std::vector<file> thistag;
	for (int i = 1; i <= n; i ++) {
		string a, b;
		cin >> a >> b;
		tag tip;
		tip.name = b, tip.explain = judge_multi(b,FILE);
		if (tip.explain == "null") {
			if (a == "+") thistag.clear();
			continue;
		}
		if (i == 1) {
			thistag = FILE[tip];
			continue;
		}
		auto it = thistag.begin();
		for (auto it = thistag.begin() ; it != thistag.end() ; it ++) {
			file u = *it;
			if (a == "+" && u.tagtype[tip]) continue;
			if (a == "-" && u.tagtype[tip] == 0) continue;
			thistag.erase(it);
		}
	}
	cout << "符合这些条件的文件共" << thistag.size() << "个" << "\n";
	for (int i = 0; i < thistag.size(); i++) {
		cout << thistag[i].getname() << "\n";
	}
	system("pause");
}
