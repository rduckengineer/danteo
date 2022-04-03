#include "user_interface/title_page_presenter.hpp"

namespace danteo {
namespace {
ftxui::Dimensions toFTX(Size2D const& box) {
    return {.dimx = static_cast<int>(box.width), .dimy = static_cast<int>(box.height)};
}

ftxui::Color toFTX(HSV color) {
    return ftxui::Color::HSV(color.hue, color.saturation, color.value);
}
}; // namespace

ftxui::Element present(TitlePage const& titlePage) {
    using namespace ftxui;

    auto boxSize = [](Size2D size2D) {
        auto const dim = toFTX(size2D);
        return size(WIDTH, EQUAL, dim.dimx) | size(HEIGHT, EQUAL, dim.dimy);
    };

    auto mainBox = flex(text(std::string{titlePage.title}) | bold | center)
                 | boxSize(titlePage.box_size) | bgcolor(toFTX(titlePage.box_color)) | border;

    return center(std::move(mainBox)) | bgcolor(toFTX(titlePage.page_color));
}
} // namespace danteo
