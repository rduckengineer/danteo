#include "reboot_scene.hpp"

#include "engine/state_graph_builder.hpp"
#include "engine/state_to_page_request_map_builder.hpp"

#include "gameplay/pages/scene_change_page.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

#include "gameplay/characters.hpp"

namespace danteo::scenes {

// cppcheck-suppress constParameter
void RebootScene::addScene(engine::StateGraph::Builder& builder) const {
    builder / SceneStates::rebootScene + Events::next   = SceneStates::youFailed;
    builder / SceneStates::youFailed + Events::next     = SceneStates::aMonthLater;
    builder / SceneStates::aMonthLater + Events::next   = SceneStates::theBotsFailed;
    builder / SceneStates::theBotsFailed + Events::next = SceneStates::noTime;
    builder / SceneStates::noTime + Events::next        = nextScene;
}

void RebootScene::addScene(DanteoStateToPageMap::Builder& builder) const {
    using namespace characters;

    builder << SceneStates::rebootScene
            << SceneChangePage{"After missing the deadline", Events::next};

    builder
        << SceneStates::youFailed
        << DialoguePageOnly{
               {DialogueBuilder::place(Virgil)
                    .left()

                    .then(Virgil)
                    .says("As you all know, we failed to meet the release deadline. Lucifer "
                          "and the board are fuming. Our quotas won't be met this quarter, and our "
                          "funding is now in the balance.")

                    .then(Virgil)
                    .says("In short, we feel that despite everyone's obvious talent here, we "
                          "haven't managed to be aggressive enough in promoting bad coding "
                          "practices.")

                    .then(Virgil)
                    .says(
                        "Which is why we will be replacing half our staff by machine-learning "
                        "algorithms trained on enterprise projects of at least 15 years of "
                        "existence, and a minimum average file size of 4000 lines! And of course, "
                        "no automated test, sanitizer, or static analyzer will be allowed.")

                    .then(Virgil)
                    .says("Let's double down on creating a buggier tomorrow!")

               },
               Events::next};

    builder << SceneStates::aMonthLater << SceneChangePage{"A Month Later", Events::next};

    builder << SceneStates::theBotsFailed
            << DialoguePageWithChoice{
                   {DialogueBuilder::place(Virgil).left().then(Virgil).says(
                       "Welcome to DantIO! We're always excited to have new recruits! I'm sure you "
                       "have tons of questions, so let's not waste any time!")},
                   std::vector<std::string>{"Why am I back?"},
                   std::vector<engine::Event>{Events::next}};

    builder << SceneStates::noTime
            << DialoguePageOnly{
                   {//
                    DialogueBuilder::place(You)
                        .right()
                        .andPlace(Virgil)
                        .left()
                        //

                        .then(You)
                        .says("Wh-")

                        .then(Virgil)
                        .says("No time, I said! The prod is on fire -literally- so it's a "
                              "all-hands-or-hooves on deck situation.")

                        .then(Virgil)
                        .says("Our new bots aren't working as expected. They're rehashing the same "
                              "patterns over and over again. The humans have realized this and "
                              "aren't reading their code anymore.")

                        .then(Virgil)
                        .says("We need creativity! Surprise! So get to it, we need to ship ASAP!")

                        .then(You)
                        .says("I-")

                        .then(Virgil)
                        .says("Get moving!")},
                   Events::next};
}

} // namespace danteo::scenes
