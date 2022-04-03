#ifndef DANTEO_COLOR_HPP
#define DANTEO_COLOR_HPP

#include <cstdint>

namespace danteo {

struct HSV {
    std::uint8_t hue;
    std::uint8_t saturation;
    std::uint8_t value;

    [[nodiscard]] constexpr bool operator==(HSV const&) const = default;
};

namespace color_literals {
constexpr HSV operator""_hsv(unsigned long long color) {
    constexpr unsigned hueOffset        = 16U;
    constexpr unsigned saturationOffset = 8U;
    constexpr unsigned valueOffset      = 0U;

    return HSV{.hue        = static_cast<uint8_t>(color >> hueOffset),
               .saturation = static_cast<uint8_t>(color >> saturationOffset),
               .value      = static_cast<uint8_t>(color >> valueOffset)};
}
} // namespace color_literals
} // namespace danteo

#endif // DANTEO_COLOR_HPP
