#ifndef DANTEO_DANTEO_STATE_GRAPH_HPP
#define DANTEO_DANTEO_STATE_GRAPH_HPP

#include "engine/state_graph.hpp"
#include "engine/state_to_page_request_map.hpp"

#include "gameplay/danteo_page_request.hpp"

#include "engine/page_navigation.hpp"

namespace danteo {

struct States {
    static constexpr engine::State titleScreen{"titleScreen"};
    static constexpr engine::State exit{"EXIT"};
};

struct Events {
    static constexpr engine::Event next{"next"};
    static constexpr engine::Event fakeRespawn{"fakeRespawn"};
};

engine::PageNavigation<DanteoPageRequest> gameNavigation();
} // namespace danteo

#endif // DANTEO_DANTEO_STATE_GRAPH_HPP
