#ifndef DANTEO_DANTEO_STATE_GRAPH_HPP
#define DANTEO_DANTEO_STATE_GRAPH_HPP

#include "engine/state_graph.hpp"
#include "engine/state_to_page_request_map.hpp"

#include "danteo_page_request.hpp"

namespace danteo {

struct States {
    static constexpr State titleScreen{"titleScreen"};
    static constexpr State secondPage{"secondPage"};
    static constexpr State exit{"EXIT"};
};

struct Events {
    static constexpr Event next{"next"};
};

StateGraph gameStateGraph();

StateToPageRequestMap<DanteoPageRequest> pagePerState();
} // namespace danteo

#endif // DANTEO_DANTEO_STATE_GRAPH_HPP
