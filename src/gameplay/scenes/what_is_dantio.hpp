#ifndef DANTEO_WHAT_IS_DANTIO_HPP
#define DANTEO_WHAT_IS_DANTIO_HPP

#include "gameplay/danteo_state_graph.hpp"
#include "engine/state_to_page_request_map.hpp"

#include "gameplay/danteo_page_request.hpp"

namespace danteo::scenes {

struct CorridorStates {
    static constexpr engine::State corridorScene{"Corridor"};
    static constexpr engine::State discussion{"Corridor discussion"};
    static constexpr engine::State buzzwords{"what is it"};
    static constexpr engine::State theClouds{"THE CLOUDS"};
    static constexpr engine::State heaven{"HEAVEN"};
    static constexpr engine::State hell{"HELL"};
    static constexpr engine::State theCloudsBis{"NO BUT THE CLOUDS"};
    static constexpr engine::State programmerPain{"My eyes..."};
    static constexpr engine::State letsGoYay{"Let's get started!"};
    static constexpr engine::State letsGoNay{"Let's get started..."};
    static constexpr engine::State imOut{"I'm out"};
};

struct CorridorEvents {
    static constexpr engine::Event HEAVEN{"heaven"};
    static constexpr engine::Event HELL{"hell"};
    static constexpr engine::Event CLOUDS{"clouds"};

    static constexpr engine::Event genius{"<3"};
    static constexpr engine::Event evil{"</3"};
};

constexpr engine::State secondSceneStart = CorridorStates::corridorScene;

struct SecondSceneExits {
    engine::State nextScene;
    engine::State restart;
};

void addSecondScene(engine::StateGraph::Builder& builder, SecondSceneExits const& exits);

void addSecondScene(std::map<engine::State, DanteoPageRequest>& pagesPerState);
} // namespace danteo::scenes

#endif // DANTEO_WHAT_IS_DANTIO_HPP
