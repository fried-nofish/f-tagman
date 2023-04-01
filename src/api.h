#include <string>
#include <map>
#include <set>
#include <vector>
#include <string_view>

//! 标签类型
struct tag_t {
    std::string name;
    std::string brief;
};

//! 标签-资源关系网络类型
using tagnet_t = std::map<tag_t *, std::set<std::string>>;

namespace api {

inline namespace v1 {

/*!
 * \brief 判断标签是否存在
 * \param [in] net: 关系网络
 * \param [in] tagName: 目标标签名
 * \return 命名为目标标签名的标签是否存在
 */
bool exists(const tagnet_t &net, std::string_view tagName);

/*!
 * \brief 判断标签是否存在
 * \param [in] net: 关系网络
 * \param [in] tagInst: 目标标签
 * \return 目标标签是否存在
 */
bool exists(const tagnet_t &net, const tag_t *tagInst);

/*!
 * \brief 从标签名获取标签列表
 * \param [in] net: 关系网络
 * \param [in] tagName: 目标标签名
 * \return 命名为目标标签名的标签列表
 */
std::vector<tag_t *>
    getTagsFromName(const tagnet_t &net, std::string_view tagName);

/*!
 * \brief 从标签获取资源列表
 * \param [in] net: 关系网络
 * \param [in] tagInst: 目标标签
 * \return 标注有目标标签的资源列表
 */
std::vector<std::string_view>
    getResoucesFromTag(const tagnet_t &net, const tag_t *tagInst);

/*!
 * \brief 获取资源的标签列表
 * \param [in] net: 关系网络
 * \param [in] url: 目标资源路径
 * \return 目标资源的标签列表
 */
std::vector<const tag_t *>
    getResoucesTags(const tagnet_t &net, std::string_view url);

/*!
 * \brief 为资源标注标签
 * \param [in] net: 关系网络
 * \param [in] url: 资源路径
 * \param [in] tagInst: 标注的标签
 * \return 目标资源是否成功被标注目标标签
 */
bool tagResource(tagnet_t &net, std::string_view url, const tag_t *tagInst);

/*!
 * \brief 为资源标注标签
 * \param [in] net: 关系网络
 * \param [in] url: 资源路径
 * \param [in] tagName: 标注的标签名
 * \param [in] handler: 标签冲突处理器
 * \return 目标资源是否成功被标注目标标签
 */
bool tagResource(
    tagnet_t                                      &net,
    std::string_view                               url,
    std::string_view                               tagName,
    std::function<void(const tagnet_t &, tag_t *)> handler);

/*!
 * \brief 取消资源的目标标签标注
 * \param [in] net: 关系网络
 * \param [in] url: 资源路径
 * \param [in] tagInst: 待取消标注的标签名
 * \return 是否成功取消目标资源的指定标签标注
 *
 * \note 当目标标签不存在或目标资源不存在指定标签时返回 false
 */
bool untagResource(tagnet_t &net, std::string_view url, const tag_t *tagInst);

}; // namespace v1

} // namespace api
