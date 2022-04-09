#include "what_is_dantio.hpp"

#include "gameplay/pages/dialogue_page_builder.hpp"
#include "gameplay/characters.hpp"

#include <array>

namespace danteo::scenes {
using namespace danteo::characters;

namespace {
DialoguePageWithChoice makeDiscussion();
DialoguePageWithChoice makeBuzzwords();
DialoguePageWithChoice makeTheClouds();
DialoguePageOnly       buildHeavenHellOrTheClouds(std::string_view chosenResponse);
DialoguePageWithChoice makeProgrammerPain();
DialoguePageOnly       buildThatsEvilOrGenius(std::string_view chosenResponse);
DialoguePageOnly       makeImOutOfHere();

struct MapInserter {
    std::map<engine::State, DanteoPageRequest>& mapToUpdate;
    engine::State                               state;
};

MapInserter operator<<(std::map<engine::State, DanteoPageRequest>& lhs, engine::State rhs) {
    return {lhs, rhs};
}

template <typename PageT>
    requires(
        std::is_constructible_v<DanteoPageRequest, PageT> && !std::is_lvalue_reference_v<PageT>)
void operator<<(MapInserter&& lhs, PageT&& rhs) {
    lhs.mapToUpdate.try_emplace(lhs.state, std::move(rhs)); // NOLINT intended move
}
} // namespace

void addSecondScene(std::map<engine::State, DanteoPageRequest>& pagesPerState) {
    pagesPerState << CorridorStates::corridorScene << SceneChangePage{"Corridor", Events::next};
    pagesPerState << CorridorStates::discussion << makeDiscussion();
    pagesPerState << CorridorStates::buzzwords << makeBuzzwords();
    pagesPerState << CorridorStates::theClouds << makeTheClouds();
    pagesPerState << CorridorStates::heaven
                  << buildHeavenHellOrTheClouds("Like the actual heaven?!");
    pagesPerState << CorridorStates::hell << buildHeavenHellOrTheClouds("Are we really in hell?!");
    pagesPerState << CorridorStates::theCloudsBis
                  << buildHeavenHellOrTheClouds("Did you mean the literal clouds?!");
    pagesPerState << CorridorStates::programmerPain << makeProgrammerPain();
    pagesPerState << CorridorStates::letsGoYay
                  << buildThatsEvilOrGenius("That's genius! Where do I sign?");
    pagesPerState << CorridorStates::letsGoNay
                  << buildThatsEvilOrGenius("That's evil! I didn't sign up for this!");
    pagesPerState << CorridorStates::imOut << makeImOutOfHere();
}

namespace {
DialoguePageWithChoice makeDiscussion() {
    return {
        {// clang-format off
         DialogueBuilder::place(PM).left()
             .andPlace(BitterSenior).right()
             // clang-format on
             .then(PM)
             .says(fmt::format("Look, {}, the KPIs still aren't good enough for the release so "
                               "far. I know you all have been working very hard on it, but is "
                               "there anything more we can do to meet the deadline?",
                               BitterSenior))

             .then(BitterSenior)
             .says("Well I told you we need more devs! We're doing our best here, but quality "
                   "takes time!")

             .then(PM)
             .says(fmt::format(
                 "Well, I asked {}. We're supposed to get fresh blood soon, but it's-", Virgil))},
        std::vector<std::string>{"*Clear your throat*"},
        std::vector<engine::Event>{Events::next}};
}

DialoguePageWithChoice makeBuzzwords() {
    return {
        {
            // clang-format off
            DialogueBuilder::place(PM).left()
             .andPlace(BitterSenior).left()
             .andPlace(You).right()

             .then(You).says("*Cough loudly*")

             .then(PM)
             .says(fmt::format(
                 "Speaking of the devil! You must be the new developer, hi! I'm "
                 "{}, the project manager, and this is {} one of our senior developers.",
                 PM, BitterSenior))

             .then(You).says("What is this place?")

             .then(BitterSenior).says("The 10th circle of Hell.")

             .then(PM)
             .says(fmt::format(
                 "Very productive, {}. DantIO is a cutting-edge platform for optimizing "
                 "crowd-sourced energy production. We want to disrupt the market by leveraging "
                 "this new infrastructure in the Clouds-",
                 BitterSenior))
            // clang-format on
        },
        std::vector<std::string>{"You mean \"the cloud\"."},
        std::vector<engine::Event>{Events::next}};
}

DialoguePageWithChoice makeTheClouds() {
    return {
        {// clang-format off
         DialogueBuilder::place(BitterSenior).left()
             .andPlace(PM).left()
             .andPlace(You).right()

             .then(You).says("You mean \"the cloud\", right?")
             // clang-format on

             .then(BitterSenior)
             .says("No no: the \"Clouds\". Ever since Heaven has migrated to this "
                   "containerized-lambdas-on-droplets architecture, they've been able to "
                   "scale their infrastructure like crazy.")

             .then(PM)
             .says("Of course, now that they have more servers than Google, they've opened up "
                   "their Clouds to 3rd parties, so the lower-downs seized the opportunity to "
                   "modernize and started DantIO")},
        std::vector<std::string>{"HEAVEN?!", "HELL?!", "THE CLOUDS?!"},
        std::vector<engine::Event>{
            CorridorEvents::HEAVEN, CorridorEvents::HELL, CorridorEvents::CLOUDS}};
}

DialoguePageOnly buildHeavenHellOrTheClouds(std::string_view chosenResponse) {
    return {

        // clang-format off
        DialogueBuilder::place(PM).left()
            .andPlace(BitterSenior).left()
            .andPlace(You).right()

            .then(You).says(std::string{chosenResponse})

            .then(PM).says("... Well, yes.")
            // clang-format on

            .then(BitterSenior)
            .says(fmt::format("Great, so no one briefed them. Thanks for nothing {}.", Virgil))

            .then(BitterSenior)
            .says("Alright, rookie, here's the deal: yes Heaven is using the clouds on Earth "
                  "to deploy lightweight containers and yes, this is Hell.")

            .then(PM)
            .says("But we're pivotting. People aren't really scared of coming here anymore, "
                  "and this was our only source of energy, so we had to find something else."),
        Events::next};
}

DialoguePageWithChoice makeProgrammerPain() {
    return {
        {// clang-format off
         DialogueBuilder::place(PM).left()
             .andPlace(BitterSenior).left()
             // clang-format on

             .then(PM)
             .says("That's when we realized that we could collect the pain developers endure "
                   "when reading bad code and turn it into a quasi-infinite source of clean "
                   "energy.")

             .then(BitterSenior)
             .says("And a lot of it is written in JavaScript, so imagine!")

             .then(PM)
             .says("Fortunately, with the ever-increasing need for automation, there is an "
                   "exponential growth of software and inexperienced developers out there.")

             .then(BitterSenior)
             .says("Our mission is to make software rot and to ensure that juniors "
                   "stay far away from good practices.")},
        std::vector<std::string>{"That's evil!", "That's genius!", "I'm out of here!"},
        std::vector<engine::Event>{
            CorridorEvents::evil, CorridorEvents::genius, Events::fakeRespawn}};
}

DialoguePageOnly buildThatsEvilOrGenius(std::string_view chosen) {
    return {{// clang-format off
             DialogueBuilder::place(PM).left()
                 .andPlace(BitterSenior).left()
                 .andPlace(You).right()

                 .then(You).says(std::string{chosen})
                 // clang-format on

                 .then(BitterSenior)
                 .says("Well if you're here, then your contract is already signed.")

                 .then(PM)
                 .says("Which means you two can get back to it, we really need to hit those "
                       "deadlines!")},
            Events::next};
}

DialoguePageOnly makeImOutOfHere() {
    return {{DialogueBuilder::place(PM)
                 .left()
                 .andPlace(You)
                 .right()

                 .then(You)
                 .says("You're insane! I'm out of here!")

                 .then(PM)
                 .says("Suit yourself. The exit is right through this door.")},
            Events::next};
}
} // namespace
} // namespace danteo::scenes
