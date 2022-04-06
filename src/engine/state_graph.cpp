#include "engine/state_graph.hpp"

namespace danteo {
std::optional<State> StateGraph::firstValidTransition(State startingState, Event event) const {
    auto transitionIt = transitions_.find(startingState);
    if (transitionIt == transitions_.end()) { return std::nullopt; }

    auto const& possibleTransitions = transitionIt->second;
    auto        foundTransition     = std::find_if(
                   possibleTransitions.begin(), possibleTransitions.end(), [&](Transition const& transition) {
            return transition.event == event && transition.isValid();
                   });

    return foundTransition != possibleTransitions.end()
             ? foundTransition->landingState
             : std::optional<State>{};
}
} // namespace danteo
