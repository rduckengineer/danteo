#include "user_interface/title_page.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

SCENARIO("Title pages describe their content") {
    static constexpr auto expectedTitle = "Test Title"sv;

    static constexpr danteo::TitlePage titlePage{.title = expectedTitle,
                                                 .box_size =
                                                     danteo::Box{.width = {5}, .height = {10}},
                                                 .box_color = danteo::HSV{0, 0, 0},
                                                 .page_color = danteo::HSV{0, 1, 0}};

    STATIC_REQUIRE(titlePage.title == expectedTitle);
    STATIC_REQUIRE(titlePage.box_size == danteo::Box{.width = {5}, .height = {10}});
    STATIC_REQUIRE(titlePage.box_color == danteo::HSV{0, 0, 0});
    STATIC_REQUIRE(titlePage.page_color == danteo::HSV{0, 1, 0});
}
