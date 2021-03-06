#include "gameplay/main_loop.hpp"

#include "engine/game_runner.hpp"
#include "user_interface/game_screen.hpp"

#include "gameplay/danteo_update_loop.hpp"

#include <ftxui/component/screen_interactive.hpp>

namespace danteo {

void mainLoop() {
    auto               screen = ftxui::ScreenInteractive::Fullscreen();
    GameScreen         gameScreen{screen};
    engine::LoopRunner runner{};

    GameUpdateLoop loop{gameScreen};

    std::thread gameThread{[&] {
        static constexpr auto startDelay = std::chrono::milliseconds{100};
        std::this_thread::sleep_for(startDelay);

        loop.initialize();

        runner.run([&](engine::GameClock::Elapsed elapsed) { return loop.update(elapsed); });
    }};

    gameScreen.runUI();
    gameThread.join();
}
} // namespace danteo
