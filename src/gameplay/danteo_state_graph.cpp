#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "gameplay/pages/dialogue_page_builder.hpp"

namespace danteo {
namespace {
constexpr auto kenobi   = Character{"Kenobi"};
constexpr auto grievous = Character{"Grievous"};
constexpr auto gerald   = Character{"Gerald"};
constexpr auto yennefer = Character{"Yennefer"};
} // namespace

engine::StateGraph gameStateGraph() {
    engine::StateGraph::Builder builder{};

    builder / States::titleScreen + Events::next  = States::dialoguePage;
    builder / States::dialoguePage + Events::next = States::secondPage;
    builder / States::secondPage + Events::next   = States::exit;

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
        States::secondPage,
        DialoguePageWithChoice{
            {
                // clang-format off
                DialogueBuilder::place(kenobi).left()
                 .andPlace(grievous).right()
                 .then(kenobi).says("Hello there.")
                 .then(grievous).says("General Kenobi!")
                // clang-format on
            },
            std::vector<std::string>{"*laugh maniacally*", "*flex your 4 lightsabers*"},
            std::vector<engine::Event>{Events::next, Events::next}});

    pagesPerState.try_emplace(
        States::dialoguePage,
        DialoguePageOnly{
            {
                // clang-format off
                DialogueBuilder::place(gerald).left()
                 .andPlace(yennefer).right()
                 .then(gerald).says("Hello Yen.")
                 .then(yennefer).says("Hello wolf.")
                // clang-format on
            },
            Events::next});

    return engine::StateToPageRequestMap{std::move(pagesPerState)};
}
} // namespace danteo
