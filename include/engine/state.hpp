#ifndef DANTEO_STATE_HPP
#define DANTEO_STATE_HPP

#include <string_view>
#include <functional>

namespace danteo {
struct State {
    std::string_view name;

    constexpr std::strong_ordering operator<=>(State const&) const = default;
};
} // namespace danteo

namespace std {
template <>
struct hash<danteo::State> {
    using is_transparent = void;
    size_t operator()(danteo::State const& state) const { return hash<string_view>{}(state.name); }
    size_t operator()(std::string_view const& state) const { return hash<string_view>{}(state); }
};

template <>
struct equal_to<danteo::State> {
    using is_transparent = void;
    constexpr bool operator()(danteo::State const& lhs, danteo::State const& rhs) const {
        return lhs.name == rhs.name;
    }
    constexpr bool operator()(std::string_view const& lhs, danteo::State const& rhs) const {
        return lhs == rhs.name;
    }
};
} // namespace std

#endif // DANTEO_STATE_HPP
