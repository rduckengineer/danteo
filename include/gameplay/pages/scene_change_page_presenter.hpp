#ifndef DANTEO_SCENE_CHANGE_PAGE_PRESENTER_HPP
#define DANTEO_SCENE_CHANGE_PAGE_PRESENTER_HPP

#include "gameplay/pages/scene_change_page.hpp"

#include <ftxui/component/component.hpp>

namespace danteo {
ftxui::Element   present(SceneChangePage const& page);
ftxui::Component pageFrom(SceneChangePage const&             page,
                          std::function<void(engine::Event)> eventHandler);

} // namespace danteo

#endif // DANTEO_SCENE_CHANGE_PAGE_PRESENTER_HPP
