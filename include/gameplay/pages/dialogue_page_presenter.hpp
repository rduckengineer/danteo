#ifndef DANTEO_DIALOGUE_PAGE_PRESENTER_HPP
#define DANTEO_DIALOGUE_PAGE_PRESENTER_HPP

#include "gameplay/pages/dialogue_page.hpp"

#include <ftxui/component/component.hpp>

namespace danteo {

ftxui::Component pageFrom(DialoguePage const&                page,
                          std::function<void(engine::Event)> eventHandler);

inline ftxui::Component pageFrom(DialoguePageWithChoice const&      page,
                                 std::function<void(engine::Event)> eventHandler) {
    return [&page, eventHandler_ = std::move(eventHandler)]() mutable {
        int selection = 0;
        return ftxui::Container::Vertical(
            {pageFrom(static_cast<DialoguePage const&>(page), std::move(eventHandler_)),
             ftxui::Menu(&page.choices, &selection)});
    }();
}

} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_PRESENTER_HPP
