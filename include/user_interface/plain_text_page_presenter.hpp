#ifndef DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
#define DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP

#include "user_interface/plain_text_page.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>

namespace danteo {

ftxui::Element present(PlainTextPage const& page) {
    return ftxui::text(std::string{page.content()});
}

ftxui::Component pageFrom(PlainTextPage const& page, std::function<void()> onNext) {
    return ftxui::Renderer([=] { return present(page); })
         | ftxui::CatchEvent(
               [&, onNext_ = std::move(onNext)](ftxui::Event event) { // NOLINT API forces the copy
                   if (event == ftxui::Event::Return) {
                       onNext_();
                       return true;
                   }
                   return false;
               });
}

} // namespace danteo

#endif // DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
