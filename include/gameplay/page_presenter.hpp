#ifndef DANTEO_PAGE_PRESENTER_HPP
#define DANTEO_PAGE_PRESENTER_HPP

#include "engine/visitor.hpp"
#include "user_interface/title_page_presenter.hpp"
#include "user_interface/plain_text_page_presenter.hpp"

#include "gameplay/danteo_state_graph.hpp"

#include "ftxui/component/component.hpp"

namespace danteo {
class PageComponentFactory {
public:
    explicit PageComponentFactory(std::function<void(Event)> eventHandler)
        : eventHandler_(std::move(eventHandler)) {}

    [[nodiscard]] ftxui::Component makePageAt(DanteoPageRequest const& request) const {
        return request.present<ftxui::Component>([&](auto const& page) -> ftxui::Component {
            return pageFrom(page, eventHandler_);
        });
    }

private:
    std::function<void(Event)> eventHandler_;
};
} // namespace danteo

#endif // DANTEO_PAGE_PRESENTER_HPP
