#include "fake_interactive_screen.hpp"

#include "user_interface/game_screen.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("The GameScreen updates the current page when running the screen loop") {
    FakeInteractiveScreen screen;
    danteo::GameScreen    presenter{screen};

    THEN("By default, the top level component has no child") {
        bool checkWasCalled = false;
        screen.mockLoop([&](ftxui::Component const& component) {
            CHECK(component->ChildCount() == 0);
            checkWasCalled = true;
            presenter.stopRunning();
        });

        presenter.runUI();
        REQUIRE(checkWasCalled);
    }

    GIVEN("A running presenter") {
        std::atomic<bool> hasSeenANewChild      = false;
        std::atomic<bool> animationWasRequested = false;

        screen.mockLoop([&](ftxui::Component const& component) {
            if (component->ChildCount() == 0) { return; }
            hasSeenANewChild = true;
        });

        screen.mockRequestAnimation([&]() { animationWasRequested = true; });

        std::thread uiThread{[&]() { presenter.runUI(); }};

        WHEN("Setting the current page from the non-UI thread") {

            presenter.setCurrentPage(ftxui::Renderer([]() { return ftxui::text("sample text"); }));

            THEN("The page is correctly set on the UI thread and the animation refresh was "
                 "requested") {
                static constexpr auto timeout = 1s;

                auto startWait = std::chrono::steady_clock::now();
                while (!hasSeenANewChild) {
                    if (std::chrono::steady_clock::now() - startWait > timeout) {
                        FAIL("Timeout expired: no child seen!");
                    }
                }
                CHECK(hasSeenANewChild);
                CHECK(animationWasRequested);
            }

            presenter.stopRunning();
            uiThread.join();
        }
    }
}
