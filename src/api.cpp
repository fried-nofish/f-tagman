#include "api.h"

#include <assert.h>
#include <stdlib.h>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>

namespace api {

inline namespace v1 {

bool exists(const tagnet_t &net, std::string_view tagName) {
    using value_type = tagnet_t::value_type;

    return std::find_if(
               net.begin(),
               net.end(),
               [tagName](const value_type &e) {
                   const auto &[key, value] = e;
                   return key->name == tagName;
               })
        != net.end();
}

bool exists(const tagnet_t &net, const tag_t *tagInst) {
    return net.find(const_cast<tag_t *>(tagInst)) != net.end();
}

std::vector<tag_t *>
    getTagsFromName(const tagnet_t &net, std::string_view tagName) {
    std::vector<tag_t *> resp{};

    auto it = std::back_inserter(resp);
    for (auto &[key, value] : net) { *it++ = key; }

    return resp;
}

std::vector<std::string_view>
    getResoucesFromTag(const tagnet_t &net, const tag_t *tagInst) {
    using value_type = tagnet_t::value_type;

    std::vector<std::string_view> resp{};

    auto it =
        std::find_if(net.begin(), net.end(), [tagInst](const value_type &e) {
            const auto &[key, value] = e;
            return key == tagInst;
        });

    if (it != net.end()) {
        const auto &resList = it->second;
        resp.assign(resList.begin(), resList.end());
    }

    return resp;
}

std::vector<const tag_t *>
    getResoucesTags(const tagnet_t &net, std::string_view url) {
    std::vector<const tag_t *> resp{};

    auto it = std::back_inserter(resp);
    for (auto &[key, value] : net) {
        if (std::find(value.begin(), value.end(), url) != value.end()) {
            *it++ = key;
        }
    }

    return resp;
}

bool tagResource(tagnet_t &net, std::string_view url, const tag_t *tagInst) {
    assert(tagInst != nullptr);

    auto tag = const_cast<tag_t *>(tagInst);

    const auto n = net.count(tag);
    assert(n <= 1);

    if (n == 1) {
        net.at(tag).insert(std::string{url});
        return true;
    }

    std::set resList{std::string{url}};
    net.insert_or_assign(tag, resList);

    return true;
}

bool tagResource(
    tagnet_t                                      &net,
    std::string_view                               url,
    std::string_view                               tagName,
    std::function<void(const tagnet_t &, tag_t *)> handler) {
    using value_type = tagnet_t::value_type;

    auto tagInst = std::unique_ptr<tag_t>(new tag_t{std::string{tagName}, ""});

    const auto result = tagResource(net, url, tagInst.get());

    if (!exists(net, tagName)) {
        tagInst.release();
        return result;
    }

    auto &resolveConflict = handler;
    auto  tagList         = getTagsFromName(net, tagName);

    for (auto &tagInst : tagList) { resolveConflict(net, tagInst); }

    //! 冲突处理检验规则
    //! 1. tagnet 存储的关系不发生变更
    //! 2. tag 的命名不发生变更
    //! 3. tag 之间的标注互斥

    auto ok = true;

    for (auto &tagInst : tagList) { ok &= net.count(tagInst) == 1; }

    for (const auto &e : tagList) { ok &= e->name == tagName; }

    std::set<std::string_view> exclusiveTestBin;
    for (const auto &e : tagList) { exclusiveTestBin.insert(e->brief); }
    ok &= exclusiveTestBin.size() == tagList.size();

    if (ok) {
        tagInst.release();
        return result;
    }

    perror("bad tag conflicts handler");
    return false;
}

bool untagResource(tagnet_t &net, std::string_view url, const tag_t *tagInst) {
    assert(tagInst != nullptr);
    auto tag = const_cast<tag_t *>(tagInst);

    assert(net.count(tag) <= 1);
    if (net.count(tag) == 0) {
        perror("specific tag does not exist");
        return false;
    }

    auto      &resList = net.at(tag);
    const auto key     = std::string{url};

    if (resList.count(key) == 0) {
        perror("target resource does not contain the specific tag");
        return false;
    }

    resList.erase(key);
    return true;
}

} // namespace v1

} // namespace api