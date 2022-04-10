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
    static constexpr engine::State gameEnd   = States::outro;

    static constexpr auto   title = "DantIO";
    static constexpr Size2D titleBoxSize{Width{50U}, Height{10U}};
    static constexpr HSV    titleBoxColor{HSV{250, 255, 50}};
    static constexpr HSV    titlePageColor{HSV{0, 0, 10}};

    scenes::WelcomeScene const  welcomeScene{.nextScene = scenes::CorridorScene::startState};
    scenes::CorridorScene const corridorScene{{.nextScene = scenes::OfficeScene::startState,
                                               .restart   = scenes::WelcomeScene::startState}};
    scenes::OfficeScene const   officeScene{.nextScene = scenes::RebootScene::startState};
    scenes::RebootScene const   rebootScene{.nextScene = gameEnd};

    auto graph = [&] {
        engine::StateGraph::Builder graphBuilder{};
        graphBuilder / States::titleScreen + Events::next = scenes::WelcomeScene::startState;
        graphBuilder / States::outro + Events::next       = States::exit;
        addScenesToGraph(graphBuilder, welcomeScene, corridorScene, officeScene, rebootScene);
        return graphBuilder;
    }();

    auto pageMap = [&] {
        DanteoStateToPageMap::Builder pagesPerState{};

        auto makeTitle = [&] {
            return TitlePage{.title      = title,
                             .box_size   = titleBoxSize,
                             .box_color  = titleBoxColor,
                             .page_color = titlePageColor,
                             .next_event = Events::next};
        };

        pagesPerState << States::titleScreen << makeTitle();

        pagesPerState << States::outro << makeTitle();

        addScenesToGraph(pagesPerState, welcomeScene, corridorScene, officeScene, rebootScene);
        return pagesPerState;
    }();

    return engine::PageNavigation{
        engine::StateMachine{std::move(graph).build(), gameStart}, std::move(pageMap).build()};
}
} // namespace danteo
