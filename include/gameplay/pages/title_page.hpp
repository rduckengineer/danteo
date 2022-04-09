#ifndef DANTEO_TITLE_PAGE_HPP
#define DANTEO_TITLE_PAGE_HPP

#include "engine/event.hpp"

#include "user_interface/size_2d.hpp"
#include "user_interface/color.hpp"

#include <string_view>

#include <compare>

namespace danteo {

struct TitlePage {
    std::string_view const title;
    Size2D const           box_size;
    HSV const              box_color;
    HSV const              page_color;
    engine::Event const    next_event;
};

} // namespace danteo

#endif // DANTEO_TITLE_PAGE_HPP
