#ifndef DANTEO_DANTEO_PAGE_REQUEST_HPP
#define DANTEO_DANTEO_PAGE_REQUEST_HPP

#include "gameplay/pages/plain_text_page.hpp"
#include "gameplay/pages/title_page.hpp"
#include "gameplay/pages/dialogue_page.hpp"

#include "engine/page_request.hpp"

namespace danteo {
using DanteoPageRequest
    = engine::PageRequest<PlainTextPage, TitlePage, DialoguePageOnly, DialoguePageWithChoice>;

static_assert(std::is_nothrow_move_constructible_v<DanteoPageRequest>,
              "New pages should be noexcept on move construction!");
} // namespace danteo

#endif // DANTEO_DANTEO_PAGE_REQUEST_HPP
