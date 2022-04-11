#ifndef DANTEO_FADE_PRESENTER_BASE_HPP
#define DANTEO_FADE_PRESENTER_BASE_HPP

#include "engine/event.hpp"

#include "user_interface/color_ftxui.hpp"

#include "ftxui/component/component_base.hpp"
#include "ftxui/component/animation.hpp"

namespace danteo {

template <typename PageT>
class FadePresenterBase : public ftxui::ComponentBase {
    static constexpr int maxHeight = 5;

public:
    FadePresenterBase(PageT const& page, std::function<void(engine::Event)> eventHandler)
        : page_{page}
        , eventHandler_{std::move(eventHandler)} {}

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

protected:
    ftxui::Color blendWithBackground(ftxui::Color targetColor) const {
        return ftxui::Color::Interpolate(fadeValue, ftxui::Color::Palette16::Black, targetColor);
    }

    PageT const& page_;

private:
    bool hasFadedToBlack() { return animator.to() == 0.F && fadeValue == 0.F; }
    void goToNext() { eventHandler_(page_.next_event); }

    std::function<void(engine::Event)> eventHandler_;
    float                              fadeValue{0.F};
    ftxui::animation::Animator         animator{&fadeValue, 1.F, std::chrono::seconds{1}};
};
} // namespace danteo

#endif // DANTEO_FADE_PRESENTER_BASE_HPP
