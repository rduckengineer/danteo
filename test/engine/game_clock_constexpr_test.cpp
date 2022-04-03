#include "engine/game_clock.hpp"

#include <catch2/catch.hpp>

namespace {
[[nodiscard]] constexpr danteo::GameClock::Elapsed bothElapsed(
    std::chrono::steady_clock::duration elapsed) {
    return {.sinceLast = elapsed, .sinceStart = elapsed};
}
} // namespace

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("The game clock tracks elapsed time") {
    using duration   = std::chrono::steady_clock::duration;
    using time_point = std::chrono::steady_clock::time_point;

    GIVEN("A starting time point") {
        static constexpr duration   timeSinceEpoch{45'121'054'155};
        static constexpr time_point startTime{timeSinceEpoch};

        static constexpr danteo::GameClock gameClock{startTime};

        THEN("The elapsed time for the starting timestamp is 0") {
            STATIC_REQUIRE(gameClock.elapsedAt(startTime) == bothElapsed(duration{0}));
        }

        WHEN("Updating once after time has passed") {
            static constexpr duration   frameTime   = duration{500};
            static constexpr time_point firstUpdate = startTime + frameTime;

            THEN("The time elapsed since start and since last have elapsed by the same amount") {
                STATIC_REQUIRE(gameClock.elapsedAt(firstUpdate) == bothElapsed(frameTime));
            }

            AND_WHEN("Updating once more after a second frame has passed") {
                static constexpr danteo::GameClock clockAfterUpdate
                    = gameClock.afterUpdateAt(firstUpdate);
                static constexpr time_point secondUpdate = firstUpdate + frameTime;

                THEN("The time elapsed since last is only one frame time") {
                    STATIC_REQUIRE(clockAfterUpdate.elapsedAt(secondUpdate)
                                   == danteo::GameClock::Elapsed{
                                       .sinceLast  = frameTime,
                                       .sinceStart = frameTime + frameTime,
                                   });
                }
            }
        }
    }
}
