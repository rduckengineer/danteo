#ifndef DANTEO_CEO_SCENE_HPP
#define DANTEO_CEO_SCENE_HPP

#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"

#include "gameplay/characters.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

namespace danteo::scenes {

constexpr engine::State firstSceneStartState = States::welcome;

void addFirstScene(engine::StateGraph::Builder& builder, // cppcheck-suppress[constParameter]
                   engine::State                nextSceneStartState) {
    builder / States::welcome + Events::next     = States::welcomeCont;
    builder / States::welcomeCont + Events::next = nextSceneStartState;
}

void addFirstScene(std::map<engine::State, DanteoPageRequest>& pagesPerState) {
    using namespace danteo::characters;
    pagesPerState.try_emplace(
        States::welcome,
        DialoguePageWithChoice{
            {DialogueBuilder::place(Virgil).left().then(Virgil).says(
                "Welcome to DantIO! We're always excited to have new recruits! I'm sure you have "
                "tons of questions, so let's not waste any time!")},
            std::vector<std::string>{"Where am I?", "Who are you?", "What am I doing here?"},
            std::vector<engine::Event>{Events::next, Events::next, Events::next}});

    pagesPerState.try_emplace(
        States::welcomeCont,
        DialoguePageOnly{
            {DialogueBuilder::place(You)
                 .right()
                 .andPlace(Virgil)
                 .left()

                 .then(You)
                 .says("Wh-")

                 .then(Virgil)
                 .says("No time, I said! The prod is on fire -literally- so it's a "
                       "all-hands-or-hooves on deck situation.")

                 .then(Virgil)
                 .says("Our output is barely keeping up with demand. QA has been rejecting our "
                       "release candidates over and over again because of the defect rate.")

                 .then(Virgil)
                 .says("I just got off a call with the lower-downs, and they're getting impatient. "
                       "So get to it, we need to ship ASAP!")

                 .then(You)
                 .says("I-")

                 .then(Virgil)
                 .says("Get moving!")},
            Events::next});
}
} // namespace danteo::scenes

#endif // DANTEO_CEO_SCENE_HPP
