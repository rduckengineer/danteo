#include "user_interface/title_page.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

SCENARIO("Title pages describe their content") {
    using danteo::Height;
    using danteo::HSV;
    using danteo::Size2D;
    using danteo::Width;

    static constexpr auto expectedTitle = "Test Title"sv;
    static constexpr auto expectedSize = Size2D{Width{5U}, Height{10U}};
    static constexpr auto expectedBoxColor = HSV{0, 0, 0};
    static constexpr auto expectedPageColor = HSV{0, 0, 0};

    [[maybe_unused]] static constexpr danteo::TitlePage titlePage{
        .title = expectedTitle,
        .box_size = expectedSize,
        .box_color = expectedBoxColor,
        .page_color = expectedPageColor};

    STATIC_REQUIRE(titlePage.title == expectedTitle);
    STATIC_REQUIRE(titlePage.box_size == expectedSize);
    STATIC_REQUIRE(titlePage.box_color == expectedBoxColor);
    STATIC_REQUIRE(titlePage.page_color == expectedPageColor);
}
