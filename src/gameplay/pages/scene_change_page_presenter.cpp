#include "gameplay/pages/scene_change_page_presenter.hpp"

#include <fmt/format.h>

#include "gameplay/pages/fade_presenter_base.hpp"

namespace danteo {

class SceneChangePagePresenter : public FadePresenterBase<SceneChangePage> {
    static constexpr int maxHeight = 5;

public:
    SceneChangePagePresenter(SceneChangePage const&             page,
                             std::function<void(engine::Event)> eventHandler)
        : FadePresenterBase<SceneChangePage>(page, std::move(eventHandler)) {}

    ftxui::Element Render() override {
        auto fgColor = blendWithBackground(ftxui::Color::Palette16::White);

        return ftxui::vbox({ftxui::filler(),
                            ftxui::text(fmt::format("[ {} ]", page_.content)) | ftxui::bold
                                | ftxui::flex | ftxui::center | ftxui::color(fgColor)
                                | ftxui::bgcolor(ftxui::Color::Palette16::Black) | ftxui::inverted
                                | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, maxHeight),
                            ftxui::filler()});
    }
};

ftxui::Component pageFrom(SceneChangePage const&             page,
                          std::function<void(engine::Event)> eventHandler) {
    return std::make_shared<SceneChangePagePresenter>(page, std::move(eventHandler));
}
} // namespace danteo
