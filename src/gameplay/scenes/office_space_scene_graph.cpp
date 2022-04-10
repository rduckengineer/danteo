#include "office_space_scene.hpp"

#include "engine/state_graph_builder.hpp"

namespace danteo::scenes {
// cppcheck-suppress constParameter
void OfficeScene::addScene(engine::StateGraph::Builder& builder) const {
    builder / SceneStates::officeScene + Events::next = nextScene;
}
} // namespace danteo::scenes
