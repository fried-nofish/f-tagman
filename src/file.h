#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
typedef int tagbool;
#include <filesystem>

using address = std::string;
struct tag;
class file {
private:
    std::string id;
    std::string name;

public:
    file() = default;

    file(std::string name, std::string id) {
        this->name = name;
        this->id   = id;
    }

    std::string getname(){
        return name;
    }

    std::string getip(){
        return id;
    }

    void changename(std::string name){
        this->name=name;
    }

    void changeip(std::string id){
        this->id=id;
    }

    file operator=(const file& f);
    std::map<tag,tagbool> tagtype;
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
void function_08(std::map < tag, std::vector<file> > &FILE);
void function_05(std::map < tag, std::vector<file> >& FILE);
void function_06(std::map < tag, std::vector<file> >& FILE);