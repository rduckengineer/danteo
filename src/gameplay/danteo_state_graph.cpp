#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

namespace danteo {
namespace {
constexpr Character                  You{"You"};
constexpr Character                  Virgil{"Virgil"};
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
    builder / States::welcomeCont + Events::next = States::exit;

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
                "Welcome to DantIO! We're always excited to have new recruits! I'm sure you have a "
                "lot of questions, so let's get them out of the way")},
            std::vector<std::string>{"Where am I?"},
            std::vector<engine::Event>{Events::next}});

    pagesPerState.try_emplace(
        States::welcomeCont,
        DialoguePageWithChoice{
            {DialogueBuilder::place(You)
                 .right()
                 .andPlace(Virgil)
                 .left()
                 .then(You)
                 .says("Where -")
                 .then(Virgil)
                 .says("Oh. Actually, no time for questions. You're already late on your sprint "
                       "goal. The customer wants to know why the load on the ingress servers in "
                       "prod. QA has been trying to reproduce the issue on the staging environment "
                       "all morning.")
                 .then(Virgil)
                 .says("Well? Get moving, I'm not paying you for slacking, go help them. I mean "
                       "I'm not paying you at all, but you still better go.")},
            std::vector<std::string>{"Where am I?"},
            std::vector<engine::Event>{Events::next}});

    return engine::StateToPageRequestMap{std::move(pagesPerState)};
}
} // namespace danteo
