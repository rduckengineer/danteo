#include "user_interface/plain_text_page.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

constexpr auto longText = R"(
This is a long text!

It is even multiline!!!)"sv;

SCENARIO("Plain text pages can describe their content") {
    static constexpr danteo::PlainTextPage page{longText};
    STATIC_REQUIRE(page.content() == longText);
}