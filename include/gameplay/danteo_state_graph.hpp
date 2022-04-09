#ifndef DANTEO_DANTEO_STATE_GRAPH_HPP
#define DANTEO_DANTEO_STATE_GRAPH_HPP

#include "engine/state_graph.hpp"
#include "engine/state_to_page_request_map.hpp"

#include "danteo_page_request.hpp"

namespace danteo {

struct States {
    static constexpr engine::State titleScreen{"titleScreen"};
    static constexpr engine::State welcome{"welcome1"};
    static constexpr engine::State welcomeCont{"welcome2"};
    static constexpr engine::State exit{"EXIT"};
};

struct Events {
    static constexpr engine::Event next{"next"};
};

engine::StateGraph gameStateGraph();

engine::StateToPageRequestMap<DanteoPageRequest> pagePerState();
} // namespace danteo

#endif // DANTEO_DANTEO_STATE_GRAPH_HPP
