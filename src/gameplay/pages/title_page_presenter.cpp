#include "gameplay/pages/title_page_presenter.hpp"

#include "gameplay/pages/fade_presenter_base.hpp"

namespace danteo {
namespace {
ftxui::Dimensions toFTX(Size2D const& box) {
    return {.dimx = static_cast<int>(box.width), .dimy = static_cast<int>(box.height)};
}
}; // namespace

class TitlePagePresenter : public FadePresenterBase<TitlePage> {
public:
    TitlePagePresenter(TitlePage const& page, std::function<void(engine::Event)> eventHandler)
        : FadePresenterBase<TitlePage>(page, std::move(eventHandler)) {}

    ftxui::Element Render() override {
        using namespace ftxui;

        auto boxSize = [](Size2D size2D) {
            auto const dim = toFTX(size2D);
            return size(WIDTH, EQUAL, dim.dimx) | size(HEIGHT, EQUAL, dim.dimy);
        };

        auto bgColor = blendWithBackground(convert::toFTX(page_.box_color));
        auto fgColor = blendWithBackground(ftxui::Color::Palette16::White);

        auto mainBox = flex(text(std::string{page_.title}) | bold | center)
                     | boxSize(page_.box_size) | bgcolor(bgColor) | border | color(fgColor);

        return center(std::move(mainBox)) | bgcolor(convert::toFTX(page_.page_color));
    }
};

ftxui::Component pageFrom(TitlePage const&                           titlePage,
                          std::function<void(danteo::engine::Event)> eventHandler) {
    return std::make_shared<TitlePagePresenter>(titlePage, std::move(eventHandler));
}
} // namespace danteo
