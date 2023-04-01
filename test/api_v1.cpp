#include <gtest/gtest.h>
#include <memory>
#include <algorithm>
#include <type_traits>

#include <api.h>

static inline bool fuzzyEqual(const auto &lhs, const auto &rhs)
    requires std::is_same_v<
        std::remove_cvref_t<decltype(lhs)>,
        std::remove_cvref_t<decltype(rhs)>>
{
    auto lhsSorted = lhs;
    auto rhsSorted = rhs;

    std::sort(lhsSorted.begin(), lhsSorted.end());
    std::sort(rhsSorted.begin(), rhsSorted.end());

    return lhsSorted == rhsSorted;
}

TEST(APIv1, tagCtor) {
    tag_t tag_1;
    tag_1.name  = "name";
    tag_1.brief = "brief";

    EXPECT_TRUE(tag_1.name == "name");
    EXPECT_TRUE(tag_1.brief == "brief");

    tag_t tag_2;

    EXPECT_TRUE(tag_2.name.empty());
    EXPECT_TRUE(tag_2.brief.empty());

    tag_t tag_3{};

    EXPECT_TRUE(tag_3.name.empty());
    EXPECT_TRUE(tag_3.brief.empty());

    tag_t tag_4{"name", "brief"};

    EXPECT_TRUE(tag_4.name == "name");
    EXPECT_TRUE(tag_4.brief == "brief");
}

TEST(APIv1, tagnetCtor) {
    tagnet_t net_1;

    EXPECT_TRUE(net_1.empty());

    tagnet_t net_2{};

    EXPECT_TRUE(net_2.empty());

    tagnet_t net_3{
        {nullptr, {}}
    };

    EXPECT_EQ(net_3.size(), 1);

    EXPECT_NO_THROW(net_3.at(nullptr));

    EXPECT_EQ(net_3.at(nullptr).size(), 0);

    auto     tag_1 = std::make_unique<tag_t>();
    tag_t    tag_2;
    tagnet_t net_4{
        {nullptr,     {}                       },
        {tag_1.get(), {"1", "2", "3"}          },
        {tag_1.get(), {"foobar"}               },
        {&tag_2,      {"1", "3", "2", "2", "4"}},
    };
    const auto ref_1 = tagnet_t::mapped_type{"1", "2", "3"};
    const auto ref_2 = tagnet_t::mapped_type{"1", "2", "3", "4"};

    EXPECT_EQ(net_4.size(), 3);

    EXPECT_NO_THROW(net_4.at(nullptr));
    EXPECT_NO_THROW(net_4.at(tag_1.get()));
    EXPECT_NO_THROW(net_4.at(&tag_2));

    EXPECT_EQ(net_4.at(nullptr).size(), 0);
    EXPECT_EQ(net_4.at(tag_1.get()).size(), 3);
    EXPECT_EQ(net_4.at(&tag_2).size(), 4);

    EXPECT_EQ(net_4.at(tag_1.get()), ref_1);
    EXPECT_EQ(net_4.at(&tag_2), ref_2);
}

TEST(APIv1, existsViaTagName) {
    auto tag_1 = std::make_unique<tag_t>();
    auto tag_2 = std::make_unique<tag_t>();
    auto tag_3 = std::make_unique<tag_t>();

    tag_1->name = "1";
    tag_2->name = "2";
    tag_3->name = "1";

    tagnet_t net{
        {tag_1.get(), {}},
        {tag_2.get(), {}},
        {tag_3.get(), {}},
    };

    EXPECT_FALSE(api::exists(net, ""));
    EXPECT_TRUE(api::exists(net, "1"));
    EXPECT_TRUE(api::exists(net, "2"));
    EXPECT_FALSE(api::exists(net, "3"));
}

TEST(APIv1, existsViaTagInst) {
    auto tag_1 = std::make_unique<tag_t>();
    auto tag_2 = std::make_unique<tag_t>();
    auto tag_3 = std::make_unique<tag_t>();
    auto tag_4 = std::make_unique<tag_t>();

    tag_1->name  = "1";
    tag_1->brief = "c1";
    tag_2->name  = "1";
    tag_2->brief = "c2";
    tag_3->name  = "1";
    tag_3->brief = "c1";
    tag_4->name  = "2";

    tagnet_t net{
        {tag_1.get(), {}},
        {tag_2.get(), {}},
        {tag_4.get(), {}},
    };

    EXPECT_TRUE(api::exists(net, tag_1.get()));
    EXPECT_TRUE(api::exists(net, tag_2.get()));
    EXPECT_FALSE(api::exists(net, tag_3.get()));
    EXPECT_TRUE(api::exists(net, tag_4.get()));
}

TEST(APIv1, getTagsFromName) {
    auto tag_1 = std::make_unique<tag_t>();
    auto tag_2 = std::make_unique<tag_t>();
    auto tag_3 = std::make_unique<tag_t>();
    auto tag_4 = std::make_unique<tag_t>();

    tag_1->name  = "1";
    tag_1->brief = "c1";
    tag_2->name  = "1";
    tag_2->brief = "c2";
    tag_3->name  = "1";
    tag_3->brief = "c1";
    tag_4->name  = "2";

    tagnet_t net{
        {tag_1.get(), {}},
        {tag_2.get(), {}},
        {tag_3.get(), {}},
        {tag_4.get(), {}},
    };

    const auto ref_1 = std::vector{tag_1.get(), tag_2.get(), tag_3.get()};
    const auto ref_2 = std::vector{tag_4.get()};
    const auto ref_3 = std::vector<tag_t *>{};

    const auto out_1 = api::getTagsFromName(net, "1");
    const auto out_2 = api::getTagsFromName(net, "2");
    const auto out_3 = api::getTagsFromName(net, "3");

    EXPECT_TRUE(fuzzyEqual(out_1, ref_1));
    EXPECT_TRUE(fuzzyEqual(out_2, ref_2));
    EXPECT_TRUE(fuzzyEqual(out_3, ref_3));
}

TEST(APIv1, getResourcesFromTag) {
    auto tag_1 = std::make_unique<tag_t>();
    auto tag_2 = std::make_unique<tag_t>();
    auto tag_3 = std::make_unique<tag_t>();

    tagnet_t net{
        {tag_1.get(), {"/a/b/c", "/b/c/a", "/c/a/b"}},
        {tag_2.get(), {}                            },
        {tag_3.get(), {"/foo/bar"}                  },
    };

    using retval_type = decltype(api::getResourcesFromTag({}, {}));

    const auto ref_1 = retval_type{"/a/b/c", "/b/c/a", "/c/a/b"};
    const auto ref_2 = retval_type{};
    const auto ref_3 = retval_type{"/foo/bar"};
    const auto ref_4 = retval_type{};

    const auto out_1 = api::getResourcesFromTag(net, tag_1.get());
    const auto out_2 = api::getResourcesFromTag(net, tag_2.get());
    const auto out_3 = api::getResourcesFromTag(net, tag_3.get());
    const auto out_4 = api::getResourcesFromTag(net, nullptr);

    EXPECT_TRUE(fuzzyEqual(out_1, ref_1));
    EXPECT_TRUE(fuzzyEqual(out_2, ref_2));
    EXPECT_TRUE(fuzzyEqual(out_3, ref_3));
    EXPECT_TRUE(fuzzyEqual(out_4, ref_4));
}

TEST(APIv1, getResourceTags) {
    auto tag_1 = std::make_unique<tag_t>();
    auto tag_2 = std::make_unique<tag_t>();
    auto tag_3 = std::make_unique<tag_t>();

    tag_1->name = "1";
    tag_2->name = "1";
    tag_3->name = "2";

    tagnet_t net{
        {tag_1.get(), {"/a/b/c", "/b/c/a", "/c/a/b"}  },
        {tag_2.get(), {"/a/b/c"}                      },
        {tag_3.get(), {"/a/b/c", "/b/c/a", "/foo/bar"}},
    };

    using retval_type = decltype(api::getResourceTags({}, {}));

    const auto ref_1 = retval_type{tag_1.get(), tag_2.get(), tag_3.get()};
    const auto ref_2 = retval_type{tag_1.get(), tag_3.get()};
    const auto ref_3 = retval_type{tag_1.get()};
    const auto ref_4 = retval_type{tag_3.get()};
    const auto ref_5 = retval_type{};

    const auto out_1 = api::getResourceTags(net, "/a/b/c");
    const auto out_2 = api::getResourceTags(net, "/b/c/a");
    const auto out_3 = api::getResourceTags(net, "/c/a/b");
    const auto out_4 = api::getResourceTags(net, "/foo/bar");
    const auto out_5 = api::getResourceTags(net, "/foobar");

    EXPECT_TRUE(fuzzyEqual(out_1, ref_1));
    EXPECT_TRUE(fuzzyEqual(out_2, ref_2));
    EXPECT_TRUE(fuzzyEqual(out_3, ref_3));
    EXPECT_TRUE(fuzzyEqual(out_4, ref_4));
    EXPECT_TRUE(fuzzyEqual(out_5, ref_5));
}

TEST(APIv1, tagResourceViaTagName) {
    auto  tag_1 = std::make_unique<tag_t>();
    auto  tag_2 = std::make_unique<tag_t>();
    auto  tag_3 = std::make_unique<tag_t>();
    tag_t tag_4{"foo", ""};

    tag_1->name = "1";
    tag_2->name = "1";
    tag_3->name = "2";

    tagnet_t net{
        {tag_1.get(), {"/a/b/c"}},
        {tag_2.get(), {"/b/c/a"}},
        {tag_3.get(), {"/c/a/b"}},
        {&tag_4,      {}        },
    };

    const auto &handlerViolateRule1 = [](const tagnet_t &net, tag_t *tagInst) {
        //! NOTE: no explicit violation actually
    };

    const auto &handlerViolateRule2 = [](const tagnet_t &net, tag_t *tagInst) {
        auto suffix = tagInst->name;
        std::reverse(suffix.begin(), suffix.end());
        tagInst->name += suffix;
    };

    const auto &handlerViolateRule3 = [](const tagnet_t &net, tag_t *tagInst) {
        tagInst->brief = "foobar";
    };

    const auto &handler = [](const tagnet_t &net, tag_t *tagInst) {
        static int id  = 0;
        tagInst->brief = std::to_string(id++);
    };

    EXPECT_FALSE(
        api::tagResource(net, "///foobar", "foo", handlerViolateRule1));
    EXPECT_TRUE(tag_4.name == "foo" && tag_4.brief.empty());
    EXPECT_FALSE(
        api::tagResource(net, "///foobar", "foo", handlerViolateRule2));
    EXPECT_TRUE(tag_4.name == "foo" && tag_4.brief.empty());
    EXPECT_FALSE(
        api::tagResource(net, "///foobar", "foo", handlerViolateRule3));
    EXPECT_TRUE(tag_4.name == "foo" && tag_4.brief.empty());

    using retval_type = decltype(api::getResourcesFromTag({}, {}));

    EXPECT_TRUE(
        fuzzyEqual(api::getResourcesFromTag(net, &tag_4), retval_type{}));

    EXPECT_TRUE(api::tagResource(net, "///foobar", "foo", handler));

    const auto out_1 = api::getResourceTags(net, "///foobar");

    EXPECT_EQ(out_1.size(), 1);
    EXPECT_TRUE(tag_4.brief == "0");
    EXPECT_TRUE(out_1[0]->brief == "1");

    EXPECT_TRUE(api::tagResource(net, "///foobar", "foo", handler));

    const auto out_2 = api::getResourceTags(net, "///foobar");
    const auto out_3 = std::vector<std::string_view>{
        tag_4.brief, out_1[0]->brief, out_2[out_1[0] == out_2[0]]->brief};

    EXPECT_EQ(out_2.size(), 2);
    EXPECT_TRUE(
        fuzzyEqual(out_3, std::vector<std::string_view>{"2", "3", "4"}));
}

TEST(APIv1, tagResourceViaTagInst) {
    auto  tag_1 = std::make_unique<tag_t>();
    auto  tag_2 = std::make_unique<tag_t>();
    auto  tag_3 = std::make_unique<tag_t>();
    tag_t tag_4{"foo", "bar"};

    tag_1->name = "1";
    tag_2->name = "1";
    tag_3->name = "2";

    tagnet_t net{
        {tag_1.get(), {"/a/b/c"}},
        {tag_2.get(), {"/b/c/a"}},
        {tag_3.get(), {"/c/a/b"}},
    };

    const auto out_1 = api::getResourceTags(net, "/foo/bar");

    EXPECT_FALSE(api::exists(net, &tag_4));
    EXPECT_EQ(out_1.size(), 0);
    EXPECT_EQ(std::find(out_1.begin(), out_1.end(), &tag_4), out_1.end());

    EXPECT_TRUE(api::tagResource(net, "/foo/bar", &tag_4));
    const auto out_2 = api::getResourceTags(net, "/foo/bar");

    EXPECT_EQ(out_2.size(), 1);
    EXPECT_TRUE(api::exists(net, &tag_4));
    EXPECT_NE(std::find(out_2.begin(), out_2.end(), &tag_4), out_2.end());

    const auto out_3 = api::getResourcesFromTag(net, tag_3.get());
    EXPECT_EQ(out_3.size(), 1);

    using retval_type = decltype(api::getResourcesFromTag({}, {}));

    EXPECT_TRUE(api::tagResource(net, "/foo/bar", tag_3.get()));
    const auto out_4 = api::getResourcesFromTag(net, tag_3.get());

    EXPECT_EQ(out_4.size(), 2);
    EXPECT_TRUE(fuzzyEqual(out_4, retval_type{"/c/a/b", "/foo/bar"}));
}

TEST(APIv1, untagResource) {
    auto  tag_1 = std::make_unique<tag_t>();
    auto  tag_2 = std::make_unique<tag_t>();
    auto  tag_3 = std::make_unique<tag_t>();
    tag_t tag_4;

    tag_1->name = "1";
    tag_2->name = "1";
    tag_3->name = "2";

    tagnet_t net{
        {tag_1.get(), {"/a/b/c", "/b/c/a", "/c/a/b"}  },
        {tag_2.get(), {"/a/b/c"}                      },
        {tag_3.get(), {"/a/b/c", "/b/c/a", "/foo/bar"}},
    };

    EXPECT_FALSE(api::untagResource(net, "/foobar", tag_1.get()));
    EXPECT_FALSE(api::untagResource(net, "/foo/bar", tag_1.get()));
    EXPECT_FALSE(api::untagResource(net, "/foobar", &tag_4));

    using retval_type = decltype(api::getResourcesFromTag({}, {}));

    EXPECT_TRUE(fuzzyEqual(
        retval_type{"/a/b/c", "/b/c/a", "/foo/bar"},
        api::getResourcesFromTag(net, tag_3.get())));

    EXPECT_TRUE(api::untagResource(net, "/foo/bar", tag_3.get()));

    EXPECT_TRUE(fuzzyEqual(
        retval_type{"/a/b/c", "/b/c/a"},
        api::getResourcesFromTag(net, tag_3.get())));

    EXPECT_FALSE(api::untagResource(net, "/foo/bar", tag_3.get()));

    EXPECT_TRUE(fuzzyEqual(
        retval_type{"/a/b/c", "/b/c/a"},
        api::getResourcesFromTag(net, tag_3.get())));

    EXPECT_TRUE(fuzzyEqual(
        retval_type{"/a/b/c"}, api::getResourcesFromTag(net, tag_2.get())));

    EXPECT_TRUE(api::untagResource(net, "/a/b/c", tag_2.get()));

    EXPECT_TRUE(
        fuzzyEqual(retval_type{}, api::getResourcesFromTag(net, tag_2.get())));
}
