#ifndef DANTEO_OFFICE_SPACE_HPP
#define DANTEO_OFFICE_SPACE_HPP

#include "engine/state_to_page_request_map.hpp"
#include "gameplay/danteo_state_to_page_map.hpp"

#include "gameplay/danteo_state_graph.hpp"

namespace danteo::scenes {
struct OfficeScene {
    engine::State nextScene;

    struct SceneStates {
        static constexpr engine::State officeScene{"TheOffice"};
    };

    static constexpr engine::State startState = SceneStates::officeScene;

    void addScene(engine::StateGraph::Builder& builder) const;
    void addScene(DanteoStateToPageMap::Builder& builder) const;
};
}

#endif // DANTEO_OFFICE_SPACE_HPP
