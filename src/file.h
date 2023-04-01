#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

using address = std::string;

class file {
private:
    std::string id;
    std::string name;

public:
    file() = default;

    file(std::string id, std::string name) {
        this->name = name;
        this->id   = id;
    }

    file operator=(const file& f);
};

struct tag {
    std::string name;
    std::string explain = "0";

    bool operator<(const tag& a) const {
        return name == a.name ? explain < a.explain : name < a.name;
    }
};

void menu();
bool getout();
bool function_01(address filepath);
void function_02(std::map<tag, std::vector<file>>& FILE);
void function_08();
