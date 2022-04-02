#ifndef DANTEO_TITLE_PAGE_HPP
#define DANTEO_TITLE_PAGE_HPP

#include <string_view>

#include <compare>

namespace danteo {

struct Width {
    unsigned val;

    [[nodiscard]] constexpr operator unsigned() const { return val; } // NOLINT implicit
};

struct Height {
    unsigned val;

    [[nodiscard]] constexpr operator unsigned() const { return val; } // NOLINT implicit
};

struct Box {
    Width  width;
    Height height;

    [[nodiscard]] constexpr std::partial_ordering operator<=>(Box const&) const = default;
};

struct HSV {
    uint8_t hue;
    uint8_t saturation;
    uint8_t value;

    [[nodiscard]] constexpr std::partial_ordering operator<=>(HSV const&) const = default;
};

struct TitlePage {
    std::string_view const title;
    Box const              box_size;
    HSV const              box_color;
    HSV const              page_color;
};

} // namespace danteo

#endif // DANTEO_TITLE_PAGE_HPP
