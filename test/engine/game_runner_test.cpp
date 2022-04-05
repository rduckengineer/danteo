#include "engine/game_runner.hpp"

#include "format_chrono.hpp"
#include <catch2/catch.hpp>

using namespace std::chrono_literals;

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("The GameRunner tries to maintain a stable update rate") {
    auto currentTime = danteo::GameClock::clock_type::now();

    auto timeSource  = [&currentTime]() -> danteo::GameClock::time_point { return currentTime; };
    auto doNothing   = []([[maybe_unused]] auto val) {};
    auto isNotCalled = []([[maybe_unused]] auto val) { FAIL(true); };
    auto updateLasts = [&](danteo::GameClock::duration duration) {
        return [&currentTime, duration]([[maybe_unused]] auto elapsed) -> bool {
            currentTime += duration;
            return true;
        };
    };
    auto checkElapseSinceLastIs = [](danteo::GameClock::duration duration) {
        return [=](danteo::GameClock::Elapsed elapsed) {
            CHECK(elapsed.sinceLast == duration);
            return false;
        };
    };
    auto checkSleepTimeIs = [](danteo::GameClock::duration duration) {
        return [=](danteo::GameClock::duration sleepTime) { REQUIRE(sleepTime == duration); };
    };

    GIVEN("A test runner") {
        danteo::GameRunner runner{danteo::GameClock{currentTime}};
        WHEN("The update takes less than the step") {
            static constexpr auto step                = 15ms;
            static constexpr auto updateTime          = 5ms;
            static constexpr auto expectedSleepTime   = 10ms;
            auto                  simulateShortUpdate = updateLasts(updateTime);

            THEN("Sleep so that the elapsed time is roughly the same as the step") {

                runner.runOneIteration(
                    simulateShortUpdate, step, timeSource, checkSleepTimeIs(expectedSleepTime));

                AND_THEN("After the sleep the elapsed time since the last update is the processing "
                         "duration plus the actual sleep time") {
                    static constexpr auto actualSleepTime = 11ms;
                    auto checkSleepTime = checkElapseSinceLastIs(updateTime + actualSleepTime);

                    currentTime += actualSleepTime;

                    runner.runOneIteration(checkSleepTime, step, timeSource, doNothing);
                }
            }
        }

        WHEN("The update takes more than the step") {
            static constexpr auto step       = 15ms;
            static constexpr auto updateTime = step + 3ms;

            THEN("Don't sleep at all") {
                auto simulateLongUpdate = updateLasts(updateTime);
                runner.runOneIteration(simulateLongUpdate, step, timeSource, isNotCalled);

                AND_THEN("It is called immediately and the elapsed time is the update time of the "
                         "previous frame") {
                    auto checkSleepTime = checkElapseSinceLastIs(updateTime);
                    runner.runOneIteration(checkSleepTime, step, timeSource, doNothing);
                }
            }
        }
    }
}
