#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

namespace danteo {
namespace {
constexpr Character                  You{"You"};
constexpr Character                  Virgil{"Virgil"};
constexpr Character                  PM{"Cerberus"};
[[maybe_unused]] constexpr Character DustyDev{"Dustin"};
[[maybe_unused]] constexpr Character FuncBro{"Alonzo"};
[[maybe_unused]] constexpr Character NoProblemo{"NP"};
[[maybe_unused]] constexpr Character BitterSenior{"BS"};
[[maybe_unused]] constexpr Character QAGuy{"QA"};
} // namespace

engine::StateGraph gameStateGraph() {
    engine::StateGraph::Builder builder{};

    builder / States::titleScreen + Events::next = States::welcome;
    builder / States::welcome + Events::next     = States::welcomeCont;
    builder / States::welcomeCont + Events::next = States::buzzwords;
    builder / States::buzzwords + Events::next   = States::theClouds;
    builder / States::theClouds + Events::next   = States::exit;

    return std::move(builder).build();
}

engine::StateToPageRequestMap<DanteoPageRequest> pagePerState() {
    std::map<engine::State, DanteoPageRequest> pagesPerState{};

    pagesPerState.try_emplace(
        States::titleScreen,
        TitlePage{.title      = "DanteO",
                  .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                  .box_color  = HSV{0, 255, 30},           // NOLINT
                  .page_color = HSV{0, 0, 10},             // NOLINT
                  .next_event = Events::next});

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
                       "all-hands-and-hooves on deck situation.")

                 .then(Virgil)
                 .says("Our output is barely keeping up with demand. QA has been rejecting our "
                       "release candidates over and over again because of the defect rate. So get "
                       "to it, we need to ship ASAP!")

                 .then(You)
                 .says("I-")

                 .then(Virgil)
                 .says("Get moving!")},
            Events::next});

    pagesPerState.try_emplace(
        States::buzzwords,
        DialoguePageWithChoice{
            {DialogueBuilder::place(PM)
                 .left()
                 .andPlace(You)
                 .right()
                 .then(PM)
                 .says("Hey, a new soul for the team!")
                 .then(You)
                 .says("What is this place?")
                 .then(PM)
                 .says("DantIO is a cutting-edge platform for optimizing crowd-sourced energy "
                       "production. The edges are indeed pretty sharp, so be careful. The "
                       "lower-ups want to disrupt the market by leveraging the clouds' "
                       "infrastructure-")},
            std::vector<std::string>{"You mean \"the cloud\"."},
            std::vector<engine::Event>{Events::next}});

    pagesPerState.try_emplace(
        States::theClouds,
        DialoguePageWithChoice{
            {DialogueBuilder::place(PM)
                 .left()
                 .andPlace(You)
                 .right()
                 .then(You)
                 .says("You mean \"the cloud\", right?")
                 .then(PM)
                 .says("No no: the clouds. Ever since Heaven has come up with their ")},
            std::vector<std::string>{"You mean \"the cloud\"."},
            std::vector<engine::Event>{Events::next}});

    return engine::StateToPageRequestMap{std::move(pagesPerState)};
}
} // namespace danteo
