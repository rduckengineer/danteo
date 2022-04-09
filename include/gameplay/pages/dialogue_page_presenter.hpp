#ifndef DANTEO_DIALOGUE_PAGE_PRESENTER_HPP
#define DANTEO_DIALOGUE_PAGE_PRESENTER_HPP

#include "gameplay/pages/dialogue_page.hpp"

#include <ftxui/component/component.hpp>

namespace danteo {

std::function<ftxui::Element()> staticPageFrom(DialoguePage const& page);

ftxui::Component pageFrom(DialoguePageOnly const&            page,
                          std::function<void(engine::Event)> eventHandler);

ftxui::Component pageFrom(DialoguePageWithChoice const&      page,
                          std::function<void(engine::Event)> eventHandler);
} // namespace danteo

#endif // DANTEO_DIALOGUE_PAGE_PRESENTER_HPP
