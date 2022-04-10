#include "office_space_scene.hpp"

#include "engine/state_graph_builder.hpp"

namespace danteo::scenes {
// cppcheck-suppress constParameter
void OfficeScene::addScene(engine::StateGraph::Builder& builder) const {
    builder / SceneStates::officeScene + Events::next = SceneStates::meetTheTeam;

    builder / SceneStates::meetTheTeam + SceneEvents::okay     = SceneStates::ooookay;
    builder / SceneStates::meetTheTeam + SceneEvents::fmtPrint = SceneStates::fmtPrint;
    builder / SceneStates::meetTheTeam + SceneEvents::globals  = SceneStates::aGlobal;
    builder / SceneStates::ooookay + SceneEvents::fmtPrint     = SceneStates::fmtPrint;
    builder / SceneStates::ooookay + SceneEvents::globals      = SceneStates::aGlobal;
    builder / SceneStates::fmtPrint + Events::next             = pairWithDusty;
    builder / SceneStates::aGlobal + Events::next              = pairWithFuncBro;
}
} // namespace danteo::scenes
