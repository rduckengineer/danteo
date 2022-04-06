#ifndef DANTEO_DANTEO_PAGE_REQUEST_HPP
#define DANTEO_DANTEO_PAGE_REQUEST_HPP

#include "user_interface/plain_text_page.hpp"
#include "user_interface/title_page.hpp"

#include "engine/page_request.hpp"

namespace danteo {
using DanteoPageRequest = PageRequest<PlainTextPage, TitlePage>;

static_assert(std::is_nothrow_move_constructible_v<DanteoPageRequest>,
              "New pages should be noexcept on move construction!");
} // namespace danteo

#endif // DANTEO_DANTEO_PAGE_REQUEST_HPP
