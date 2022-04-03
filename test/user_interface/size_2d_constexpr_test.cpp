#include "user_interface/size_2d.hpp"

#include <catch2/catch.hpp>

using danteo::Height;
using danteo::Width;

template <typename T, typename Arg>
concept ImplicitlyConstructible = requires(Arg arg) {
    {T{arg}};
};

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE("Width and Height cannot be mistaken for each other") {

    THEN("Width cannot be used as a Height") {
        STATIC_REQUIRE(!std::assignable_from<Width, Height>);
        STATIC_REQUIRE(!std::convertible_to<Width, Height>);
        STATIC_REQUIRE(!std::constructible_from<Width, Height>);
        STATIC_REQUIRE(!ImplicitlyConstructible<Width, Height>);
    }

    THEN("Height cannot be used as a Width") {
        STATIC_REQUIRE(!std::assignable_from<Height, Width>);
        STATIC_REQUIRE(!std::convertible_to<Height, Width>);
        STATIC_REQUIRE(!std::constructible_from<Height, Width>);
        STATIC_REQUIRE(!ImplicitlyConstructible<Height, Width>);
    }
}

TEST_CASE("Width and Height can be compared to each other") {
    STATIC_REQUIRE(std::three_way_comparable_with<Width, Height, std::strong_ordering>);
    STATIC_REQUIRE(std::three_way_comparable_with<Height, Width, std::strong_ordering>);
}
