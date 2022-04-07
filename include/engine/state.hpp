#ifndef DANTEO_STATE_HPP
#define DANTEO_STATE_HPP

#include <string_view>
#include <functional>

namespace danteo::engine {
struct State {
    std::string_view name;

    constexpr std::strong_ordering operator<=>(State const&) const = default;
};
} // namespace danteo::engine

namespace std {
template <>
struct hash<danteo::engine::State> {
    using is_transparent = void;
    size_t operator()(danteo::engine::State const& state) const {
        return hash<string_view>{}(state.name);
    }
    size_t operator()(std::string_view const& state) const { return hash<string_view>{}(state); }
};

template <>
struct equal_to<danteo::engine::State> {
    using is_transparent = void;
    constexpr bool operator()(danteo::engine::State const& lhs,
                              danteo::engine::State const& rhs) const {
        return lhs.name == rhs.name;
    }
    constexpr bool operator()(std::string_view const& lhs, danteo::engine::State const& rhs) const {
        return lhs == rhs.name;
    }
};
} // namespace std

#endif // DANTEO_STATE_HPP
