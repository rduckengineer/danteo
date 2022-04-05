#ifndef DANTEO_VISITOR_HPP
#define DANTEO_VISITOR_HPP

#include <utility>

namespace danteo {
template <typename... Base>
struct Visitor : Base... {
    template <typename... T>
    constexpr Visitor(T&&... t) // cppcheck-suppress[noExplicitConstructor] makes no sense here
        : Base{std::forward<T>(t)}... {}

    using Base::operator()...;
};

template <typename... Overload>
Visitor(Overload...) -> Visitor<std::decay_t<Overload>...>;
}

#endif // DANTEO_VISITOR_HPP
