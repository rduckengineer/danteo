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
            static constexpr auto step              = 15ms;
            static constexpr auto updateTime        = 5ms;
            static constexpr auto expectedSleepTime = 10ms;

            THEN("Sleep so that the elapsed time is roughly the same as the step") {
                runner.runOneIteration(
                    updateLasts(updateTime), step, timeSource, checkSleepTimeIs(expectedSleepTime));

                AND_THEN("After the sleep the elapsed time since the last update is the processing "
                         "duration plus the actual sleep time") {
                    static constexpr auto actualSleepTime = 11ms;

                    currentTime += actualSleepTime;

                    runner.runOneIteration(checkElapseSinceLastIs(updateTime + actualSleepTime),
                                           step, timeSource, doNothing);
                }
            }
        }

        WHEN("The update takes more than the step") {
            static constexpr auto step       = 15ms;
            static constexpr auto updateTime = step + 3ms;

            THEN("Don't sleep at all") {
                runner.runOneIteration(updateLasts(updateTime), step, timeSource, isNotCalled);

                AND_THEN("It is called immediately and the elapsed time is the update time of the "
                         "previous frame") {
                    runner.runOneIteration(
                        checkElapseSinceLastIs(updateTime), step, timeSource, doNothing);
                }
            }
        }
    }
}
