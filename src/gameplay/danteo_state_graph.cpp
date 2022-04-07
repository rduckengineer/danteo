#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"

namespace danteo {
StateGraph gameStateGraph() {
    StateGraph::Builder builder{};

    builder / States::titleScreen + Events::next = States::secondPage;
    builder / States::secondPage + Events::next  = States::exit;

    return std::move(builder).build();
}
StateToPageRequestMap<DanteoPageRequest> pagePerState() {
    return StateToPageRequestMap{std::map<State, DanteoPageRequest>{
        {States::titleScreen,
         DanteoPageRequest{TitlePage{.title      = "DanteO",
                                     .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                                     .box_color  = HSV{0, 255, 30},           // NOLINT
                                     .page_color = HSV{0, 0, 10},             // NOLINT
                                     .next_event = Events::next}}},
        {States::secondPage, DanteoPageRequest{PlainTextPage{"Hello there.", Events::next}}}}};
}
} // namespace danteo
