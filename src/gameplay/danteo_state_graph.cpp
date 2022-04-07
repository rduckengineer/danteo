#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"

#include <string>

namespace danteo {
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
            {Events::next,
             std::vector{
                 DialogueLine{.character = Character{"Kenobi"},
                              .line      = "Hello there.",
                              .aligned   = DialogueLine::Aligned::Left},
                 DialogueLine{.character = Character{"Grievous"},
                              .line      = "General Kenobi!",
                              .aligned   = DialogueLine::Aligned::Right},
             }},
            std::vector<std::string>{"choice1", "choice2"}});

    pagesPerState.try_emplace(
        States::dialoguePage,
        DialoguePage{
            Events::next,
            std::vector{
                DialogueLine{Character{"Gerald"}, "Hello Yenifer.", DialogueLine::Aligned::Left},
                DialogueLine{Character{"Yen"}, "Hello wolf", DialogueLine::Aligned::Right}}});

    return engine::StateToPageRequestMap{std::move(pagesPerState)};
}
} // namespace danteo
