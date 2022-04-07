#ifndef DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
#define DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP

#include "gameplay/plain_text_page.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

namespace danteo {

inline ftxui::Element present(PlainTextPage const& page) {
    return ftxui::text(std::string{page.content});
}

inline ftxui::Component pageFrom(PlainTextPage const&               page,
                                 std::function<void(danteo::Event)> eventHandler) {
    return ftxui::Renderer([=] { return present(page); })
         | ftxui::CatchEvent([&, eventHandler_ = std::move(eventHandler)](
                                 ftxui::Event event) { // NOLINT API forces the copy
               if (event == ftxui::Event::Return) {
                   eventHandler_(page.next_event);
                   return true;
               }
               return false;
           });
}

} // namespace danteo

#endif // DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
