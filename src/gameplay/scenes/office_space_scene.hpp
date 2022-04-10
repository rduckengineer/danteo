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
        static constexpr engine::State meetTheTeam{"The H Team"};
        static constexpr engine::State ooookay{"...Okay"};
        static constexpr engine::State fmtPrint{"fmtPrint"};
        static constexpr engine::State aGlobal{"A global???"};
    };

    struct SceneEvents {
        static constexpr engine::Event okay{"Okay"};
        static constexpr engine::Event fmtPrint{"fmtPrint"};
        static constexpr engine::Event globals{"globals"};
    };

    static constexpr engine::State startState = SceneStates::officeScene;

    void addScene(engine::StateGraph::Builder& builder) const;
    void addScene(DanteoStateToPageMap::Builder& builder) const;
};
} // namespace danteo::scenes

#endif // DANTEO_OFFICE_SPACE_HPP
