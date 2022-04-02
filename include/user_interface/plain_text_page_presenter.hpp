#ifndef DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
#define DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP

#include "user_interface/plain_text_page.hpp"

#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>

namespace danteo {

template <typename T> ftxui::Element present(T const&);

template <> ftxui::Element present(PlainTextPage const& page) {
    return ftxui::text(std::string{page.content()});
}
} // namespace danteo

#endif // DANTEO_PLAIN_TEXT_PAGE_PRESENTER_HPP
