#ifndef DANTEO_STATE_GRAPH_HPP
#define DANTEO_STATE_GRAPH_HPP

#include "engine/event.hpp"
#include "engine/state.hpp"
#include <map>
#include <optional>
#include <vector>

namespace danteo {

class StateGraph {
    struct Transition {
        Event                 event;
        State                 landingState;
        std::function<bool()> isValid = []() { return true; };
    };

public:
    class Builder;

    explicit StateGraph(std::map<State, std::vector<Transition>> transitions)
        : transitions_{std::move(transitions)} {}

    [[nodiscard]] std::optional<State> firstValidTransition(State startingState, Event event) const;

private:
    std::map<State, std::vector<Transition>> const transitions_;
};
} // namespace danteo

#endif // DANTEO_STATE_GRAPH_HPP
