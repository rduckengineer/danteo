#ifndef DANTEO_TITLE_PAGE_PRESENTER_HPP
#define DANTEO_TITLE_PAGE_PRESENTER_HPP

#include "user_interface/title_page.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component_base.hpp>

namespace danteo {
ftxui::Element   present(TitlePage const& titlePage);
ftxui::Component pageFrom(TitlePage const&                   titlePage,
                          std::function<void(danteo::Event)> eventHandler);
} // namespace danteo

#endif // DANTEO_TITLE_PAGE_PRESENTER_HPP
