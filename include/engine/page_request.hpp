#ifndef DANTEO_PAGE_REQUEST_HPP
#define DANTEO_PAGE_REQUEST_HPP

#include <variant>

namespace danteo::engine {
template <typename... PageSet>
class PageRequest {
public:
    using page_set_type = std::variant<PageSet...>;

    // cppcheck-suppress[passedByValue] passing by value then moving
    constexpr explicit PageRequest(page_set_type page) noexcept(
        std::is_nothrow_move_constructible_v<page_set_type>)
        : page_{std::move(page)} {}

    template <typename R, typename Visitor>
        requires(std::is_invocable_r_v<R, Visitor, PageSet> || ...)
    [[nodiscard]] constexpr R present(Visitor visitor) const {
        return std::visit<R>(std::forward<Visitor>(visitor), page_);
    }

private:
    page_set_type page_;
};
} // namespace danteo::engine

#endif // DANTEO_PAGE_REQUEST_HPP
