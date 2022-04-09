#include "gameplay/pages/scene_change_page_presenter.hpp"

#include <ftxui/screen/screen.hpp>
#include <catch2/catch.hpp>

using namespace std::string_view_literals;

SCENARIO("Plain text pages can be rendered on a Screen") {
    GIVEN("A PlainTextPage") {
        danteo::SceneChangePage page{"Content"sv, danteo::engine::Event{"next"sv}};

        AND_GIVEN("A Screen") {
            using ftxui::Dimensions;

            auto screen = ftxui::Screen::Create(
                Dimensions{.dimx = 10, .dimy = 1}); // NOLINT numbers are named

            WHEN("Rendering to the screen") {
                ftxui::Render(screen, danteo::present(page));

                THEN("The screen contains the content") {
                    CHECK(screen.ToString() == "Content   "sv);
                }
            }
        }
    }
}
