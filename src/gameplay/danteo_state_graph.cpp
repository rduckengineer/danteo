#include "gameplay/danteo_state_graph.hpp"

#include "engine/state_graph_builder.hpp"
#include "engine/state_to_page_request_map_builder.hpp"
#include "gameplay/characters.hpp"
#include "gameplay/danteo_state_to_page_map.hpp"

#include "scenes/ceo_scene.hpp"
#include "scenes/what_is_dantio.hpp"
#include "scenes/office_space_scene.hpp"
#include "scenes/reboot_scene.hpp"

#include "scenes/scene.hpp"

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
    static constexpr engine::State gameStart = States::titleScreen;
    // static constexpr engine::State gameStart = scenes::OfficeScene::startState;

    scenes::WelcomeScene const  welcomeScene{.nextScene = scenes::CorridorScene::startState};
    scenes::CorridorScene const corridorScene{{.nextScene = scenes::OfficeScene::startState,
                                               .restart   = scenes::WelcomeScene::startState}};
    scenes::OfficeScene const   officeScene{.nextScene = scenes::RebootScene::startState};
    scenes::RebootScene const   rebootScene{.nextScene = States::exit};

    engine::StateGraph::Builder graphBuilder{};
    graphBuilder / States::titleScreen + Events::next = scenes::WelcomeScene::startState;
    addScenesToGraph(graphBuilder, welcomeScene, corridorScene, officeScene, rebootScene);

    DanteoStateToPageMap::Builder pagesPerState{};
    pagesPerState << States::titleScreen
                  << TitlePage{.title      = "DantIO",
                               .box_size   = {Width{50U}, Height{10U}}, // NOLINT
                               .box_color  = HSV{0, 255, 30},           // NOLINT
                               .page_color = HSV{0, 0, 10},             // NOLINT
                               .next_event = Events::next};
    addScenesToGraph(pagesPerState, welcomeScene, corridorScene, officeScene, rebootScene);

    return engine::PageNavigation{engine::StateMachine{std::move(graphBuilder).build(), gameStart},
                                  std::move(pagesPerState).build()};
}
} // namespace danteo
