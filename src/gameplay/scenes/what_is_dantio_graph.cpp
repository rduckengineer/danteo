#include "what_is_dantio.hpp"

#include "engine/state_graph_builder.hpp"

namespace danteo::scenes {

// cppcheck-suppress[constParameter] No, it can't be const, it's being mutated here
void CorridorScene::addScene(engine::StateGraph::Builder& builder) const {
    builder / SceneStates::corridorScene + Events::next = SceneStates::discussion;
    builder / SceneStates::discussion + Events::next    = SceneStates::buzzwords;
    builder / SceneStates::buzzwords + Events::next     = SceneStates::theClouds;

    builder / SceneStates::theClouds + SceneEvents::HELL   = SceneStates::hell;
    builder / SceneStates::theClouds + SceneEvents::HEAVEN = SceneStates::heaven;
    builder / SceneStates::theClouds + SceneEvents::CLOUDS = SceneStates::theCloudsBis;

    builder / SceneStates::hell + Events::next         = SceneStates::programmerPain;
    builder / SceneStates::heaven + Events::next       = SceneStates::programmerPain;
    builder / SceneStates::theCloudsBis + Events::next = SceneStates::programmerPain;

    builder / SceneStates::programmerPain + SceneEvents::genius = SceneStates::letsGoYay;
    builder / SceneStates::programmerPain + SceneEvents::evil   = SceneStates::letsGoNay;
    builder / SceneStates::programmerPain + Events::fakeRespawn = SceneStates::imOut;

    builder / SceneStates::letsGoYay + Events::next = nextScene_;
    builder / SceneStates::letsGoNay + Events::next = nextScene_;

    builder / SceneStates::imOut + Events::next = restart_;
}
} // namespace danteo::scenes
