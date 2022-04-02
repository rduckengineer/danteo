#ifndef DANTEO_PLAIN_TEXT_PAGE_HPP
#define DANTEO_PLAIN_TEXT_PAGE_HPP

#include <string_view>

namespace danteo {
class PlainTextPage {
public:
    explicit constexpr PlainTextPage(std::string_view textContent) noexcept
        : content_{textContent} {}

    [[nodiscard]] constexpr auto content() const noexcept { return content_; }

private:
    std::string_view content_;
};
} // namespace danteo

#endif // DANTEO_PLAIN_TEXT_PAGE_HPP
