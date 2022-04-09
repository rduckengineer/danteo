#ifndef DANTEO_WHAT_IS_DANTIO_HPP
#define DANTEO_WHAT_IS_DANTIO_HPP

#include "engine/state_graph.hpp"
#include "engine/state_to_page_request_map.hpp"

#include "gameplay/danteo_page_request.hpp"

namespace danteo::scenes {

struct CorridorStates {
    static constexpr engine::State discussion{"Corridor discussion"};
    static constexpr engine::State buzzwords{"what is it"};
    static constexpr engine::State theClouds{"THE CLOUDS"};
    static constexpr engine::State heaven{"HEAVEN"};
    static constexpr engine::State hell{"HELL"};
    static constexpr engine::State theCloudsBis{"NO BUT THE CLOUDS"};
    static constexpr engine::State programmerPain{"My eyes..."};
    static constexpr engine::State letsGoYay{"Let's get started!"};
    static constexpr engine::State letsGoNay{"Let's get started..."};
};

struct CorridorEvents {
    static constexpr engine::Event HEAVEN{"heaven"};
    static constexpr engine::Event HELL{"hell"};
    static constexpr engine::Event CLOUDS{"clouds"};

    static constexpr engine::Event genius{"<3"};
    static constexpr engine::Event evil{"</3"};
};

constexpr engine::State secondSceneStart = States::corridorScene;
void addSecondScene(engine::StateGraph::Builder& builder, // cppcheck-suppress[constParameter]
                    engine::State                nextSceneStartState) {

    builder / States::corridorScene + Events::next      = CorridorStates::discussion;
    builder / CorridorStates::discussion + Events::next = CorridorStates::buzzwords;
    builder / CorridorStates::buzzwords + Events::next  = CorridorStates::theClouds;

    builder / CorridorStates::theClouds + CorridorEvents::HELL   = CorridorStates::hell;
    builder / CorridorStates::theClouds + CorridorEvents::HEAVEN = CorridorStates::heaven;
    builder / CorridorStates::theClouds + CorridorEvents::CLOUDS = CorridorStates::theCloudsBis;

    builder / CorridorStates::hell + Events::next         = CorridorStates::programmerPain;
    builder / CorridorStates::heaven + Events::next       = CorridorStates::programmerPain;
    builder / CorridorStates::theCloudsBis + Events::next = CorridorStates::programmerPain;

    builder / CorridorStates::programmerPain + CorridorEvents::genius = CorridorStates::letsGoYay;
    builder / CorridorStates::programmerPain + CorridorEvents::evil   = CorridorStates::letsGoNay;
    builder / CorridorStates::programmerPain + Events::fakeRespawn    = nextSceneStartState;

    builder / CorridorStates::letsGoYay + Events::next = nextSceneStartState;
    builder / CorridorStates::letsGoNay + Events::next = nextSceneStartState;
}

void addSecondScene(std::map<engine::State, DanteoPageRequest>& pagesPerState) {
    using namespace danteo::characters;

    pagesPerState.try_emplace(
        States::corridorScene, SceneChangePage{"In the corridor", Events::next});

    pagesPerState.try_emplace(
        CorridorStates::discussion,
        DialoguePageWithChoice{
            {DialogueBuilder::place(PM)
                 .left()
                 .andPlace(BitterSenior)
                 .right()

                 .then(PM)
                 .says(fmt::format("Look, {}, the KPIs still aren't good enough for the release "
                                   "far. I know you all have been working very hard on it, but is "
                                   "there anything more we can do to meet the deadline?",
                                   BitterSenior))

                 .then(BitterSenior)
                 .says("Well I told you we need more devs! We're doing our best here, but quality "
                       "takes time!")

                 .then(PM)
                 .says(fmt::format(
                     "Well, I asked {}. We're supposed to get fresh blood soon, but it's-", Virgil))

            },
            std::vector<std::string>{"*Clear your throat*"},
            std::vector<engine::Event>{Events::next}});

    pagesPerState.try_emplace(
        CorridorStates::buzzwords,
        DialoguePageWithChoice{
            {

                DialogueBuilder::place(PM)
                    .left()
                    .andPlace(BitterSenior)
                    .left()
                    .andPlace(You)
                    .right()

                    .then(You)
                    .says("*Cough loudly*")

                    .then(PM)
                    .says(fmt::format(
                        "Speaking of the devil! You must be the new developer, hi! I'm "
                        "{}, the project manager, and this is {} one of our senior developers.",
                        PM, BitterSenior))

                    .then(You)
                    .says("What is this place?")

                    .then(BitterSenior)
                    .says("Hell.")

                    .then(PM)
                    .says(fmt::format(
                        "Very productive, {}. DantIO is a cutting-edge platform for optimizing "
                        "crowd-sourced energy "
                        "production. We want to disrupt the market by leveraging the Clouds "
                        "infrastructure-",
                        BitterSenior))

            },
            std::vector<std::string>{"You mean \"the cloud\"."},
            std::vector<engine::Event>{Events::next}});

    pagesPerState.try_emplace(
        CorridorStates::theClouds,
        DialoguePageWithChoice{
            {

                DialogueBuilder::place(BitterSenior)
                    .left()
                    .andPlace(PM)
                    .left()
                    .andPlace(You)
                    .right()

                    .then(You)
                    .says("You mean \"the cloud\", right?")

                    .then(BitterSenior)
                    .says("No no: the \"Clouds\". Ever since Heaven has migrated to this "
                          "containerized-lambdas-on-droplets architecture, they've been able to "
                          "scale their infrastructure like crazy.")

                    .then(PM)
                    .says(
                        "Of course, now that they have more servers than Google, they've opened up "
                        "their Clouds to 3rd parties, so the lower-downs seized the opportunity to "
                        "modernize and started DantIO")},

            std::vector<std::string>{"HEAVEN?!", "HELL?!", "THE CLOUDS?!"},
            std::vector<engine::Event>{
                CorridorEvents::HEAVEN, CorridorEvents::HELL, CorridorEvents::CLOUDS}});

    auto buildHeavenHellOrTheClouds = [&](std::string_view chosenResponse) {
        return DialoguePageOnly{

            DialogueBuilder::place(PM)
                .left()
                .andPlace(BitterSenior)
                .left()
                .andPlace(You)
                .right()

                .then(You)
                .says(std::string{chosenResponse})

                .then(PM)
                .says("... Well, yes.")

                .then(BitterSenior)
                .says(fmt::format("Great, so no one briefed them. Thanks for nothing {}.", Virgil))

                .then(BitterSenior)
                .says("Alright, rookie, here's the deal: yes Heaven is using the clouds on Earth "
                      "to deploy lightweight containers and yes, this is Hell.")

                .then(PM)
                .says("But we're pivotting. People aren't really scared of coming here anymore, "
                      "and this was our only source of energy, so we had to find something else."),

            Events::next};
    };

    pagesPerState.try_emplace(
        CorridorStates::heaven, buildHeavenHellOrTheClouds("Like the actual heaven?!"));
    pagesPerState.try_emplace(
        CorridorStates::hell, buildHeavenHellOrTheClouds("Are we really in hell?!"));
    pagesPerState.try_emplace(CorridorStates::theCloudsBis,
                              buildHeavenHellOrTheClouds("Did you mean the literal clouds?!"));

    pagesPerState.try_emplace(
        CorridorStates::programmerPain,
        DialoguePageWithChoice{
            {DialogueBuilder::place(PM)
                 .left()
                 .andPlace(BitterSenior)
                 .left()

                 .then(PM)
                 .says("That's when we realized that we could collect the pain developers endure "
                       "when reading bad code and turn it into a quasi-infinite source of clean "
                       "energy.")

                 .then(BitterSenior)
                 .says("And a lot of it is written in JavaScript, so imagine!")

                 .then(PM)
                 .says("Fortunately, with the ever-increasing need for automation, there is an "
                       "exponential growth of software out there.")

                 .then(BitterSenior)
                 .says("Our job -our MISSION!- is to make software rot and to ensure that juniors "
                       "stay away from good practices.")

            },
            std::vector<std::string>{"That's evil!", "That's genius!", "I'm out of here!"},
            std::vector<engine::Event>{
                CorridorEvents::evil, CorridorEvents::genius, Events::fakeRespawn}});

    auto buildThatsEvilOrGenius = [](std::string_view chosen) {
        return DialoguePageOnly{
            {DialogueBuilder::place(PM)
                 .left()
                 .andPlace(BitterSenior)
                 .left()
                 .andPlace(You)
                 .right()

                 .then(You)
                 .says(std::string{chosen})

                 .then(BitterSenior)
                 .says("Well if you're here, then your contract is already signed.")

                 .then(PM)
                 .says("Which means you two can get back to it, we really need to hit those "
                       "deadlines!")

            },
            Events::next};
    };

    pagesPerState.try_emplace(
        CorridorStates::letsGoYay, buildThatsEvilOrGenius("That's genius! Where do I sign?"));

    pagesPerState.try_emplace(CorridorStates::letsGoNay,
                              buildThatsEvilOrGenius("That's evil! I didn't sign up for this!"));
}
} // namespace danteo::scenes

#endif // DANTEO_WHAT_IS_DANTIO_HPP
