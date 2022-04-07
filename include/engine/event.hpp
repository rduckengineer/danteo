#ifndef DANTEO_EVENT_HPP
#define DANTEO_EVENT_HPP

#include <functional>
#include <string_view>

namespace danteo::engine {
struct Event {
    std::string_view name;

    constexpr bool operator==(Event const&) const = default;
};
} // namespace danteo::engine

namespace std {
template <>
struct hash<danteo::engine::Event> {
    using is_transparent = void;
    size_t operator()(danteo::engine::Event const& event) const {
        return hash<string_view>{}(event.name);
    }
    size_t operator()(std::string_view const& event) const { return hash<string_view>{}(event); }
};

template <>
struct equal_to<danteo::engine::Event> {
    using is_transparent = void;
    constexpr bool operator()(danteo::engine::Event const& lhs,
                              danteo::engine::Event const& rhs) const {
        return lhs.name == rhs.name;
    }
    constexpr bool operator()(std::string_view const& lhs, danteo::engine::Event const& rhs) const {
        return lhs == rhs.name;
    }
};
} // namespace std

#endif // DANTEO_EVENT_HPP
