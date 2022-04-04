#include "user_interface/main_loop.hpp"

#include "user_interface/game_presenter.hpp"
#include "user_interface/title_page_presenter.hpp"

#include "engine/game_runner.hpp"

#include <ftxui/component/screen_interactive.hpp>

namespace danteo {
void mainLoop() {
    auto          screen = ftxui::ScreenInteractive::Fullscreen();
    GamePresenter renderer{screen};
    GameRunner    runner{};

    auto update = [&](GameClock::Elapsed elapsed) -> bool {
        static constexpr auto startDelay = std::chrono::milliseconds{100};

        if (elapsed.sinceStart < startDelay) { return true; }

        static constexpr danteo::TitlePage titlePage{
            .title      = "DanteO",
            .box_size   = {Width{50U}, Height{10U}},
            .box_color  = danteo::HSV{0, 255, 30},
            .page_color = danteo::HSV{0, 0, 10}};

        renderer.setCurrentPage(pageFromTitle(titlePage, screen.ExitLoopClosure()));
        return false;
    };

    std::thread gameThread{[&] { runner.run(update); }};
    renderer.runUI();
    gameThread.join();
}
} // namespace danteo
