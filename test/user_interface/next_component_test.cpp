#include "user_interface/next_component.hpp"

#include <catch2/catch.hpp>

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("NextComponent reacts to return key presses") {
    bool callbackCalled = false;
    auto callback = [&callbackCalled] { callbackCalled = true; };

    danteo::NextComponent nextComponent{callback};

    THEN("The callback is not called on construction") { CHECK_FALSE(callbackCalled); }

    WHEN("Pressing ENTER") {
        bool wasHandled = nextComponent.OnEvent(ftxui::Event::Return);

        THEN("Even was handled and the callback was called") {
            CHECK(wasHandled);
            CHECK(callbackCalled);
        }
    }

    WHEN("Any other event happens") {
        using ftxui::Event;
        auto const event = GENERATE_COPY(Event::Character('c'), Event::CursorReporting("", 0, 0),
                                         Event::Special(""));
        bool       wasHandled = nextComponent.OnEvent(event);

        THEN("Nothing happens") {
            CHECK_FALSE(wasHandled);
            CHECK_FALSE(callbackCalled);
        }
    }
}
