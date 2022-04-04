#include "user_interface/main_loop.hpp"

#include "engine/game_clock.hpp"

#include "user_interface/title_page_presenter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <utility>

#include <concepts>

namespace danteo {

template <typename T>
concept FTXScreen = requires(T screen) {
    {screen.Post(ftxui::Task{})};
    {screen.Loop(ftxui::Component{})};
    {screen.RequestAnimationFrame()};
};

template <FTXScreen Screen>
class GamePresenter {
public:
    explicit GamePresenter(Screen& screen)
        : screen_{screen} {}

    void setCurrentPage(ftxui::Component page) {
        // This way the page is being swapped on the UI thread, and while the Screen is not trying
        // to access the component, so this function should be thread-safe
        screen_.Post(ftxui::Task{[this, heldPage = std::move(page)]() mutable {
            topLevel->DetachAllChildren();
            topLevel->Add(std::move(heldPage));
            screen_.RequestAnimationFrame();
        }});
    }

    void runUI() { screen_.Loop(topLevel); }

private:
    Screen&          screen_;
    ftxui::Component topLevel = ftxui::Make<ftxui::ComponentBase>();
};

template <typename T>
concept UpdateCallback = std::is_invocable_r_v<bool, T, GameClock::Elapsed>;

class GameRunner {
public:
    constexpr explicit GameRunner(GameClock gameClock = GameClock{GameClock::clock_type ::now()})
        : gameClock_{std::move(gameClock)} {}

    void run(UpdateCallback auto update) {
        while (true) {
            if (!update(gameClock_.tick())) { break; }
        }
    }

private:
    GameClock gameClock_;
};

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
