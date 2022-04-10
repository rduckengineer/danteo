#ifndef DANTEO_DANTEO_STATE_TO_PAGE_MAP_HPP
#define DANTEO_DANTEO_STATE_TO_PAGE_MAP_HPP

#include "engine/state_to_page_request_map.hpp"

#include "gameplay/danteo_page_request.hpp"

namespace danteo {
using DanteoStateToPageMap = engine::StateToPageRequestMap<DanteoPageRequest>;
}

#endif // DANTEO_DANTEO_STATE_TO_PAGE_MAP_HPP
