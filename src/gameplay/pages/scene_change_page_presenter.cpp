#include "gameplay/pages/scene_change_page_presenter.hpp"

#include <fmt/format.h>

#include "user_interface/color_ftxui.hpp"

#include "ftxui/component/animation.hpp"

namespace danteo {

class SceneChangePagePresenter : public ftxui::ComponentBase {
    static constexpr int maxHeight = 5;

public:
    SceneChangePagePresenter(SceneChangePage const&             page,
                             std::function<void(engine::Event)> eventHandler)
        : eventHandler_{std::move(eventHandler)}
        , page_{page} {}

    ftxui::Element Render() override {
        auto fgColor = blendWithBackground(ftxui::Color::Palette16::White);

        return ftxui::vbox({ftxui::filler(),
                            ftxui::text(fmt::format("[ {} ]", page_.content)) | ftxui::bold
                                | ftxui::flex | ftxui::center | ftxui::color(fgColor)
                                | ftxui::bgcolor(ftxui::Color::Palette16::Black) | ftxui::inverted
                                | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, maxHeight),
                            ftxui::filler()});
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
        return ftxui::Color::Interpolate(fadeValue, ftxui::Color::Palette16::Black, targetColor);
    }
    bool hasFadedToBlack() { return animator.to() == 0.F && fadeValue == 0.F; }
    void goToNext() { eventHandler_(page_.next_event); }

    std::function<void(engine::Event)> eventHandler_;
    SceneChangePage const&             page_;
    float                              fadeValue{0.F};
    ftxui::animation::Animator         animator{&fadeValue, 1.F, std::chrono::seconds{1}};
};

ftxui::Component pageFrom(SceneChangePage const&             page,
                          std::function<void(engine::Event)> eventHandler) {
    return std::make_shared<SceneChangePagePresenter>(page, std::move(eventHandler));
}
} // namespace danteo
