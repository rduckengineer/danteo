#ifndef DANTEO_SCENE_HPP
#define DANTEO_SCENE_HPP

#include "engine/state_graph.hpp"
#include "gameplay/danteo_state_to_page_map.hpp"

namespace danteo::scenes {

template <typename SceneT>
concept Scene = requires(SceneT const& scene, DanteoStateToPageMap::Builder& mapBuilder,
                         engine::StateGraph::Builder& graphBuilder) {
    std::same_as<decltype(SceneT::startState), engine::State const&>;
    {scene.startState != engine::State{}};

    {scene.addScene(graphBuilder)};
    {scene.addScene(mapBuilder)};
};

} // namespace danteo::scenes

#endif // DANTEO_SCENE_HPP
