#include "user_interface/main_loop.hpp"

#include "engine/game_clock.hpp"

#include "user_interface/title_page_presenter.hpp"
#include "user_interface/next_component.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace danteo {
class GameRenderer : public ftxui::ComponentBase {
public:
    explicit GameRenderer(std::function<void()> exitCallback,
                          GameClock             clock = GameClock{GameClock::clock_type::now()})
        : exitCallback_{std::move(exitCallback)}
        , clock_{std::move(clock)} {

        constexpr danteo::TitlePage titlePage{
            .title      = "DanteO",
            .box_size   = {Width{50U}, Height{10U}},
            .box_color  = danteo::HSV{0, 255, 30},
            .page_color = danteo::HSV{0, 0, 10}};

        auto pageRenderer = ftxui::Renderer([titlePage] { return danteo::present(titlePage); });

        Add(ftxui::CatchEvent(
            std::move(pageRenderer), [this](ftxui::Event event) { // NOLINT API forces copy
                return handleReturn(event);
            }));
    }

    ftxui::Element Render() override {
        [[maybe_unused]] auto const elapsed = clock_.updateAt(GameClock::clock_type::now());
        return ChildAt(0)->Render();
    }

private:
    [[nodiscard]] bool handleReturn(ftxui::Event const& event) const {
        if (event == ftxui::Event::Return) {
            exitCallback_();
            return true;
        }
        return false;
    }

    std::function<void()> exitCallback_;
    GameClock             clock_;
};

void mainLoop() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    auto gameRenderer = ftxui::Make<GameRenderer>(screen.ExitLoopClosure());

    screen.Loop(gameRenderer);
}
} // namespace danteo
