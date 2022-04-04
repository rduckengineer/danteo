#ifndef DANTEO_GAME_RUNNER_HPP
#define DANTEO_GAME_RUNNER_HPP

#include "engine/game_clock.hpp"

#include <type_traits>
#include <thread>

namespace danteo {

template <typename T>
concept UpdateCallback = std::is_invocable_r_v<bool, T, GameClock::Elapsed>;

template <typename T>
concept TimeSource = std::is_invocable_r_v<GameClock::time_point, T>;

template <typename T>
concept SleepFn = std::is_invocable_r_v<void, T, GameClock::duration>;

class GameRunner {
public:
    static constexpr GameClock::duration defaultStep = std::chrono::milliseconds{16};

    constexpr explicit GameRunner(GameClock gameClock = GameClock{GameClock::clock_type::now()})
        : gameClock_{std::move(gameClock)} {}

    void run(UpdateCallback auto update, GameClock::duration step = defaultStep) {
        auto const thread_sleep_for
            = &std::this_thread::sleep_for<GameClock::duration::rep, GameClock::duration::period>;

        while (true) {
            if (!runOneIteration(update, step, GameClock::clock_type::now, thread_sleep_for)) {
                break;
            }
        }
    }

    bool runOneIteration(UpdateCallback auto update, GameClock::duration const step,
                         TimeSource auto timeSource, SleepFn auto sleepFunc) {
        auto frameStart = timeSource();
        if (!update(gameClock_.tick(frameStart))) { return false; }
        auto frameEnd = timeSource();

        auto elapsed = frameEnd - frameStart;
        if (elapsed < step) { sleepFunc(step - elapsed); }
        return true;
    }

private:
    GameClock gameClock_;
};

} // namespace danteo

#endif // DANTEO_GAME_RUNNER_HPP
