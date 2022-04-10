#include "office_space_scene.hpp"

#include "engine/state_to_page_request_map_builder.hpp"

#include "gameplay/pages/scene_change_page.hpp"

namespace danteo::scenes {
// NOLINTNEXTLINE not static to keep options open
void OfficeScene::addScene(DanteoStateToPageMap::Builder& builder) const {
    builder << SceneStates::officeScene << SceneChangePage{"Office Space", Events::next};
}
} // namespace danteo::scenes
