#ifndef DANTEO_DANTEO_PAGE_COMPONENT_FACTORY_HPP
#define DANTEO_DANTEO_PAGE_COMPONENT_FACTORY_HPP

#include "gameplay/pages/title_page_presenter.hpp"
#include "gameplay/pages/scene_change_page_presenter.hpp"
#include "gameplay/pages/dialogue_page_presenter.hpp"
#include "gameplay/danteo_page_request.hpp"

#include "ftxui/component/component.hpp"

namespace danteo {
class DanteoPageComponentFactory {
public:
    explicit DanteoPageComponentFactory(std::function<void(engine::Event)> eventHandler)
        : eventHandler_(std::move(eventHandler)) {}

    [[nodiscard]] ftxui::Component makePageAt(DanteoPageRequest const& request) const {
        return request.present<ftxui::Component>([&](auto const& page) -> ftxui::Component {
            return pageFrom(page, eventHandler_);
        });
    }

private:
    std::function<void(engine::Event)> eventHandler_;
};
} // namespace danteo

#endif // DANTEO_DANTEO_PAGE_COMPONENT_FACTORY_HPP
