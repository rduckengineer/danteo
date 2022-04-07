#ifndef DANTEO_PLAIN_TEXT_PAGE_HPP
#define DANTEO_PLAIN_TEXT_PAGE_HPP

#include "engine/event.hpp"

#include <string_view>

namespace danteo {
struct PlainTextPage {
    std::string_view const content;
    Event const            next_event;
};
} // namespace danteo

#endif // DANTEO_PLAIN_TEXT_PAGE_HPP
