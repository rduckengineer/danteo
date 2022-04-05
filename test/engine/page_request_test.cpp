#include "engine/page_request.hpp"
#include "engine/visitor.hpp"

#include <catch2/catch.hpp>

using namespace std::string_view_literals;

struct TestTitlePage {
    std::string_view title;
};

struct TestExitPage {
    std::string_view farewell;
};

using TestPageRequest = danteo::PageRequest<TestTitlePage, TestExitPage>;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("A page request specifies the content of a page") {
    GIVEN("A page presenter") {
        auto presenterMatchingString
            = [](std::string_view expected) { // cppcheck-suppress[passedByValue]
                                              // string_view by copy
                  return danteo::Visitor{
                      [=](TestTitlePage page) -> bool { return page.title == expected; },
                      [=](TestExitPage page) -> bool { return page.farewell == expected; }};
              };

        AND_GIVEN("A request made from one type") {
            constexpr auto            expectedTitle = "Awesome Title!"sv;
            constexpr TestPageRequest request{TestTitlePage{expectedTitle}};

            WHEN("Visiting the request with the presenter") {
                constexpr bool hasMatched
                    = request.present<bool>(presenterMatchingString(expectedTitle));

                THEN("The content is correctly found") { STATIC_REQUIRE(hasMatched); }
            }
        }

        AND_GIVEN("A request made from another type") {
            constexpr auto            expectedFarewell = "Are you still there?"sv;
            constexpr TestPageRequest request{TestExitPage{expectedFarewell}};

            WHEN("Visiting the request with the presenter") {
                constexpr bool hasMatched
                    = request.present<bool>(presenterMatchingString(expectedFarewell));

                THEN("The content is correctly found") { STATIC_REQUIRE(hasMatched); }
            }
        }
    }
}
