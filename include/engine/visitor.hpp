#ifndef DANTEO_VISITOR_HPP
#define DANTEO_VISITOR_HPP

#include <utility>

namespace danteo {
template <typename... Overload>
struct Visitor : Overload... {

    constexpr Visitor(Overload&&... overload) // NOLINT explicit makes no sense here
        : Overload{std::forward<Overload>(overload)}... {}

    using Overload::operator()...; // NOLINT somehow one of the tools can't parse this
};

template <typename... Overload>
Visitor(Overload...) -> Visitor<std::decay_t<Overload>...>;
} // namespace danteo

#endif // DANTEO_VISITOR_HPP
