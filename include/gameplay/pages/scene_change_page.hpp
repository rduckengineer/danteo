#ifndef DANTEO_SCENE_CHANGE_PAGE_HPP
#define DANTEO_SCENE_CHANGE_PAGE_HPP

#include "engine/event.hpp"

#include <string_view>

namespace danteo {
struct SceneChangePage {
    std::string_view const content;
    engine::Event const    next_event;
};
} // namespace danteo

#endif // DANTEO_SCENE_CHANGE_PAGE_HPP
