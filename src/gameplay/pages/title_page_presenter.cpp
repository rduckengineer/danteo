#include "gameplay/pages/title_page_presenter.hpp"

#include "user_interface/color_ftxui.hpp"

#include "ftxui/component/animation.hpp"

namespace danteo {
namespace {
ftxui::Dimensions toFTX(Size2D const& box) {
    return {.dimx = static_cast<int>(box.width), .dimy = static_cast<int>(box.height)};
}
}; // namespace

class TitlePagePresenter : public ftxui::ComponentBase {
public:
    TitlePagePresenter(TitlePage const& page, std::function<void(engine::Event)> eventHandler)
        : eventHandler_{std::move(eventHandler)}
        , page_{page} {}

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

    bool OnEvent(ftxui::Event event) override {
        if (event == ftxui::Event::Return) {
            animator = ftxui::animation::Animator{&fadeValue, 0.F, std::chrono::seconds{1}};
            return true;
        }
        return false;
    }

    void OnAnimation(ftxui::animation::Params& params) override {
        animator.OnAnimation(params);

        if (hasFadedToBlack()) { goToNext(); }
    }

private:
    ftxui::Color blendWithBackground(ftxui::Color targetColor) const {
        return ftxui::Color::Interpolate(fadeValue, convert::toFTX(page_.page_color), targetColor);
    }
    bool hasFadedToBlack() { return animator.to() == 0.F && fadeValue == 0.F; }
    void goToNext() { eventHandler_(page_.next_event); }

    std::function<void(engine::Event)> eventHandler_;
    TitlePage const&                   page_;
    float                              fadeValue{0.F};
    ftxui::animation::Animator         animator{&fadeValue, 1.F, std::chrono::seconds{2}};
};

ftxui::Component pageFrom(TitlePage const&                           titlePage,
                          std::function<void(danteo::engine::Event)> eventHandler) {
    return std::make_shared<TitlePagePresenter>(titlePage, std::move(eventHandler));
}
} // namespace danteo
