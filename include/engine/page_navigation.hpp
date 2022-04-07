#ifndef DANTEO_PAGE_NAVIGATION_HPP
#define DANTEO_PAGE_NAVIGATION_HPP

#include "engine/state_machine.hpp"
#include "engine/state_to_page_request_map.hpp"

#include <fmt/format.h>

namespace danteo {
template <typename RequestT>
class PageNavigation {
public:
    explicit PageNavigation(StateMachine stateMachine, StateToPageRequestMap<RequestT> requestMap)
        : stateMachine_{std::move(stateMachine)}
        , requestMap_{std::move(requestMap)} {}

    std::optional<State> changeState(std::optional<Event> event) {
        if (!event) { return std::nullopt; }
        return stateMachine_.when(*event);
    }

    [[nodiscard]] RequestT const& pageRequested() const {
        return pageForState(stateMachine_.state());
    }

private:
    [[nodiscard]] RequestT const& pageForState(State state) const {

        auto maybePageRequest = requestMap_.pageFor(state);
        if (!maybePageRequest) {
            throw std::logic_error{
                fmt::format("There is no page corresponding to the state '{}'", state.name)};
        }
        return *maybePageRequest;
    }

    StateMachine                    stateMachine_;
    StateToPageRequestMap<RequestT> requestMap_;
};
} // namespace danteo

#endif // DANTEO_PAGENAVIGATION_HPP
