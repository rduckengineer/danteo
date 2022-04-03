#ifndef DANTEO_SIZE_2D_HPP
#define DANTEO_SIZE_2D_HPP

#include <compare>
#include <concepts>

namespace danteo {

template <typename Tag>
struct StrongTypedef {
    template <std::unsigned_integral T>
    constexpr explicit StrongTypedef(T width)
        : val{width} {}
    unsigned val;

    [[nodiscard]] constexpr operator unsigned() const { return val; } // NOLINT implicit
};

using Width = StrongTypedef<struct WidthTag>;

using Height = StrongTypedef<struct HeightTag>;

struct Size2D {
    Width  width;
    Height height;

    [[nodiscard]] constexpr std::partial_ordering operator<=>(Size2D const&) const = default;
};
} // namespace danteo

#endif // DANTEO_SIZE_2D_HPP
