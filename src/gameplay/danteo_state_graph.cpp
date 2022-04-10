#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "engine/state_to_page_request_map_builder.hpp"
#include "gameplay/characters.hpp"
#include "gameplay/danteo_state_to_page_map.hpp"

#include "scenes/ceo_scene.hpp"
#include "scenes/what_is_dantio.hpp"

namespace danteo {

template <scenes::Scene... SceneT>
void addScenesToGraph(engine::StateGraph::Builder& builder, SceneT const&... scene) {
    (scene.addScene(builder), ...);
}

engine::StateGraph gameStateGraph() {
    engine::StateGraph::Builder graphBuilder{};

    graphBuilder / States::titleScreen + Events::next = scenes::WelcomeScene::startState;

    scenes::WelcomeScene const      welcomeScene{.nextScene = scenes::CorridorScene::startState};
    constexpr scenes::CorridorScene corridorScene{
        {.nextScene = States::exit, .restart = scenes::WelcomeScene::startState}};

    addScenesToGraph(graphBuilder, welcomeScene, corridorScene);

    return std::move(graphBuilder).build();
}

DanteoStateToPageMap pagePerState() {
    DanteoStateToPageMap::Builder pagesPerState{};

    using namespace characters;

    pagesPerState << States::titleScreen
                  << TitlePage{.title      = "DantIO",
                               .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                               .box_color  = HSV{0, 255, 30},           // NOLINT
                               .page_color = HSV{0, 0, 10},             // NOLINT
                               .next_event = Events::next};

    return std::move(pagesPerState).build();
}
} // namespace danteo
