#include "user_interface/plain_text_page_presenter.hpp"

#include <ftxui/screen/screen.hpp>
#include <catch2/catch.hpp>

using namespace std::string_view_literals;

SCENARIO("Plain text pages can be rendered on a Screen") {
    GIVEN("A PlainTextPage") {
        [[maybe_unused]] danteo::PlainTextPage page{"Content"sv};

        AND_GIVEN("A Screen") {
            ftxui::Screen screen{10, 1}; // NOLINT magic numbers

            WHEN("Rendering to the screen") {
                ftxui::Render(screen, danteo::present(page));

                THEN("The screen contains the content") {
                    CHECK(screen.ToString() == "Content   "sv);
                }
            }
        }
    }
}
