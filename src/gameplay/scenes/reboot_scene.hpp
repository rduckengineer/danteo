#ifndef DANTEO_REBOOT_SCENE_HPP
#define DANTEO_REBOOT_SCENE_HPP

#include "engine/state_to_page_request_map.hpp"
#include "gameplay/danteo_state_to_page_map.hpp"

#include "gameplay/danteo_state_graph.hpp"

namespace danteo::scenes {

struct RebootScene {
    engine::State nextScene;

    struct SceneStates {
        static constexpr engine::State rebootScene{"Have you tried turning it off and on again?"};
        static constexpr engine::State youFailed{"Sucks to be you"};
        static constexpr engine::State aMonthLater{"well that was quick"};
        static constexpr engine::State theBotsFailed{"Sucks to be me"};
        static constexpr engine::State noTime{"No it actually sucks to be you. Forever."};
    };

    static constexpr engine::State startState = SceneStates::rebootScene;

    void addScene(engine::StateGraph::Builder& builder) const;
    void addScene(DanteoStateToPageMap::Builder& builder) const;
};
} // namespace danteo::scenes

#endif // DANTEO_REBOOT_SCENE_HPP
