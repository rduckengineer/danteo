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

template <scenes::Scene... SceneT>
void addScenesToGraph(DanteoStateToPageMap::Builder& builder, SceneT const&... scene) {
    (scene.addScene(builder), ...);
}

engine::PageNavigation<DanteoPageRequest> gameNavigation() {
    scenes::WelcomeScene const  welcomeScene{.nextScene = scenes::CorridorScene::startState};
    scenes::CorridorScene const corridorScene{
        {.nextScene = States::exit, .restart = scenes::WelcomeScene::startState}};

    engine::StateGraph::Builder graphBuilder{};
    graphBuilder / States::titleScreen + Events::next = scenes::WelcomeScene::startState;
    addScenesToGraph(graphBuilder, welcomeScene, corridorScene);

    DanteoStateToPageMap::Builder pagesPerState{};
    pagesPerState << States::titleScreen
                  << TitlePage{.title      = "DantIO",
                               .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                               .box_color  = HSV{0, 255, 30},           // NOLINT
                               .page_color = HSV{0, 0, 10},             // NOLINT
                               .next_event = Events::next};
    addScenesToGraph(pagesPerState, welcomeScene, corridorScene);

    return engine::PageNavigation{
        engine::StateMachine{std::move(graphBuilder).build(), States::titleScreen},
        std::move(pagesPerState).build()};
}
} // namespace danteo
