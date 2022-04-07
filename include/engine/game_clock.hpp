#ifndef DANTEO_GAME_CLOCK_HPP
#define DANTEO_GAME_CLOCK_HPP

#include <chrono>

namespace danteo::engine {
class GameClock {
public:
    using clock_type = std::chrono::steady_clock;
    using duration   = clock_type::duration;
    using time_point = clock_type::time_point;

    struct Elapsed {
        clock_type::duration const sinceLast;
        clock_type::duration const sinceStart;

        [[nodiscard]] bool operator==(Elapsed const&) const = default;
    };

    constexpr explicit GameClock(clock_type::time_point start) noexcept
        : start_{start}
        , lastUpdate_{start} {}

    [[nodiscard]] Elapsed tick(clock_type::time_point now = clock_type::now()) noexcept {
        auto delta  = elapsedAt(now);
        lastUpdate_ = now;
        return delta;
    }

    [[nodiscard]] constexpr Elapsed elapsedAt(clock_type::time_point now) const noexcept {
        return Elapsed{.sinceLast = now - lastUpdate_, .sinceStart = now - start_};
    }

    [[nodiscard]] consteval GameClock afterUpdateAt(clock_type::time_point now) const noexcept {
        return GameClock{start_, now};
    }

private:
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters) User code doesn't have access to this
    consteval explicit GameClock(clock_type::time_point start, clock_type::time_point updatedAt)
        : start_{start}
        , lastUpdate_{updatedAt} {}

    clock_type::time_point const start_;
    clock_type::time_point       lastUpdate_;
};
} // namespace danteo::engine

#endif // DANTEO_GAME_CLOCK_HPP
