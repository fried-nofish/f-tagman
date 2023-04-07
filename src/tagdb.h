#pragma once

#include <string_view>
#include <memory>

struct TagDBPrivate;

class TagDB {
public:
    TagDB(std::string_view target);
    ~TagDB();

    bool avalaible() const;

protected:
    bool initialize();

private:
    std::unique_ptr<TagDBPrivate> d;
};
