#include "file.h"

// 用于实现file类中的方法

file file::operator=(const file& f) {
    return file(f.id, f.name);
}