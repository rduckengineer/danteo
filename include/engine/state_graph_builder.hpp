#ifndef DANTEO_STATE_GRAPH_BUILDER_HPP
#define DANTEO_STATE_GRAPH_BUILDER_HPP

#include "engine/state_graph.hpp"

namespace danteo {

class StateGraph::Builder {
    class TransitionListBuilder;

    class TransitionBuilder {
        friend class TransitionListBuilder;

        TransitionBuilder(
            Builder& parent, State startingState, Event event,
            std::function<bool()> predicate = [] { return true; })
            : parent_{parent}
            , startingState_{startingState}
            , event_{event}
            , predicate_{std::move(predicate)} {}

        Builder&              parent_;
        State                 startingState_;
        Event                 event_;
        std::function<bool()> predicate_;

    public:
        TransitionBuilder operator|(std::function<bool()> predicate) && {
            predicate_ = std::move(predicate);
            return std::move(*this);
        }

        // NOLINTNEXTLINE[cppcoreguidelines-c-copy-assignment-signature] intended to be different
        void operator=(State landingState) && {
            parent_.transitions[startingState_].push_back(
                Transition{event_, landingState, std::move(predicate_)});
        }
    };

    class TransitionListBuilder {
        friend Builder;
        friend TransitionBuilder;
        TransitionListBuilder(Builder& parent, State startingState)
            : parent_(parent)
            , startingState_{startingState} {}
        Builder& parent_;
        State    startingState_;

    public:
        TransitionBuilder operator+(Event event) && {
            return TransitionBuilder{parent_, startingState_, event};
        }
    };

public:
    TransitionListBuilder operator/(State startingState) { return {*this, startingState}; }

    [[nodiscard]] StateGraph build() && { return StateGraph{std::move(transitions)}; }

private:
    std::map<State, std::vector<Transition>> transitions;
};
} // namespace danteo

#endif // DANTEO_STATE_GRAPH_BUILDER_HPP
