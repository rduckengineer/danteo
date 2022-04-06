#ifndef DANTEO_STATE_MACHINE_HPP
#define DANTEO_STATE_MACHINE_HPP

#include "engine/state_graph.hpp"

namespace danteo {

class StateMachine {
public:
    explicit StateMachine(StateGraph graph, State initialState)
        : graph_{std::move(graph)}
        , currentState_{initialState} {}

    [[nodiscard]] State  state() const { return {currentState_}; }

    std::optional<State> when(Event event) {
        auto maybeTransition = graph_.firstValidTransition(currentState_, event);
        currentState_        = maybeTransition.value_or(currentState_);
        return maybeTransition;
    }

private:
    StateGraph graph_;
    State      currentState_;
};

} // namespace danteo

#endif // DANTEO_STATE_MACHINE_HPP
