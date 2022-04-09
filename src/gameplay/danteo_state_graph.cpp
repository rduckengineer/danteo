#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "gameplay/characters.hpp"

#include "scenes/ceo_scene.hpp"
#include "scenes/what_is_dantio.hpp"

namespace danteo {

engine::StateGraph gameStateGraph() {
    engine::StateGraph::Builder builder{};

    builder / States::titleScreen + Events::next = scenes::firstSceneStartState;
    scenes::addFirstScene(builder, scenes::secondSceneStart);
    scenes::addSecondScene(builder, States::exit);

    return std::move(builder).build();
}

engine::StateToPageRequestMap<DanteoPageRequest> pagePerState() {
    std::map<engine::State, DanteoPageRequest> pagesPerState{};

    using namespace characters;

    pagesPerState.try_emplace(
        States::titleScreen,
        TitlePage{.title      = "DantIO",
                  .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                  .box_color  = HSV{0, 255, 30},           // NOLINT
                  .page_color = HSV{0, 0, 10},             // NOLINT
                  .next_event = Events::next});

    scenes::addFirstScene(pagesPerState);
    scenes::addSecondScene(pagesPerState);

    return engine::StateToPageRequestMap{std::move(pagesPerState)};
}
} // namespace danteo
