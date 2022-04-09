#include "what_is_dantio.hpp"

#include "engine/state_graph_builder.hpp"

namespace danteo {
// cppcheck-suppress[constParameter]
void scenes::addSecondScene(engine::StateGraph::Builder& builder, engine::State nextSceneStartState,
                            engine::State restart) {

    builder / CorridorStates::corridorScene + Events::next = CorridorStates::discussion;
    builder / CorridorStates::discussion + Events::next    = CorridorStates::buzzwords;
    builder / CorridorStates::buzzwords + Events::next     = CorridorStates::theClouds;

    builder / CorridorStates::theClouds + CorridorEvents::HELL   = CorridorStates::hell;
    builder / CorridorStates::theClouds + CorridorEvents::HEAVEN = CorridorStates::heaven;
    builder / CorridorStates::theClouds + CorridorEvents::CLOUDS = CorridorStates::theCloudsBis;

    builder / CorridorStates::hell + Events::next         = CorridorStates::programmerPain;
    builder / CorridorStates::heaven + Events::next       = CorridorStates::programmerPain;
    builder / CorridorStates::theCloudsBis + Events::next = CorridorStates::programmerPain;

    builder / CorridorStates::programmerPain + CorridorEvents::genius = CorridorStates::letsGoYay;
    builder / CorridorStates::programmerPain + CorridorEvents::evil   = CorridorStates::letsGoNay;
    builder / CorridorStates::programmerPain + Events::fakeRespawn    = CorridorStates::imOut;

    builder / CorridorStates::letsGoYay + Events::next = nextSceneStartState;
    builder / CorridorStates::letsGoNay + Events::next = nextSceneStartState;

    builder / CorridorStates::imOut + Events::next = restart;
}
} // namespace danteo
