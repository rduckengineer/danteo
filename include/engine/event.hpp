#ifndef DANTEO_EVENT_HPP
#define DANTEO_EVENT_HPP

#include <functional>
#include <string_view>

namespace danteo {
struct Event {
    std::string_view name;

    constexpr bool operator==(Event const&) const = default;
};
} // namespace danteo

namespace std {
template <>
struct hash<danteo::Event> {
    using is_transparent = void;
    size_t operator()(danteo::Event const& event) const { return hash<string_view>{}(event.name); }
    size_t operator()(std::string_view const& event) const { return hash<string_view>{}(event); }
};

template <>
struct equal_to<danteo::Event> {
    using is_transparent = void;
    constexpr bool operator()(danteo::Event const& lhs, danteo::Event const& rhs) const {
        return lhs.name == rhs.name;
    }
    constexpr bool operator()(std::string_view const& lhs, danteo::Event const& rhs) const {
        return lhs == rhs.name;
    }
};
} // namespace std

#endif // DANTEO_EVENT_HPP
