#include "user_interface/color.hpp"

#include <catch2/catch.hpp>

#include <concepts>

using namespace danteo::color_literals;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("HSV colors are equality comparable") {
    STATIC_REQUIRE(std::equality_comparable<danteo::HSV>);
    STATIC_REQUIRE(!std::three_way_comparable<danteo::HSV>);

    STATIC_REQUIRE(danteo::HSV{0, 0, 0} == danteo::HSV{0, 0, 0});
    STATIC_REQUIRE(danteo::HSV{254, 173, 3} == danteo::HSV{254, 173, 3});

    STATIC_REQUIRE(danteo::HSV{0, 0, 0} != danteo::HSV{0, 0, 1});
    STATIC_REQUIRE(danteo::HSV{0, 0, 0} != danteo::HSV{0, 1, 0});
    STATIC_REQUIRE(danteo::HSV{0, 0, 0} != danteo::HSV{1, 0, 0});

    STATIC_REQUIRE(0xFF4210_hsv == danteo::HSV{0xFF, 0x42, 0x10});
    STATIC_REQUIRE(0xFF4210_hsv == danteo::HSV{0xFF, 0x42, 0x10});
}
