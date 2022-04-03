#ifndef DANTEO_TITLE_PAGE_HPP
#define DANTEO_TITLE_PAGE_HPP

#include "user_interface/size_2d.hpp"

#include <string_view>

#include <compare>

namespace danteo {

struct HSV {
    uint8_t hue;
    uint8_t saturation;
    uint8_t value;

    [[nodiscard]] constexpr std::partial_ordering operator<=>(HSV const&) const = default;
};

struct TitlePage {
    std::string_view const title;
    Size2D const           box_size;
    HSV const              box_color;
    HSV const              page_color;
};

} // namespace danteo

#endif // DANTEO_TITLE_PAGE_HPP
