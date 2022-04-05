#ifndef DANTEO_DANTEO_PAGE_REQUEST_HPP
#define DANTEO_DANTEO_PAGE_REQUEST_HPP

#include "user_interface/plain_text_page.hpp"
#include "user_interface/title_page.hpp"

#include "engine/page_request.hpp"

namespace danteo {
using DanteoPageRequest = PageRequest<PlainTextPage, TitlePage>;
}

#endif // DANTEO_DANTEO_PAGE_REQUEST_HPP
