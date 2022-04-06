#include "user_interface/main_loop.hpp"

#include "user_interface/game_presenter.hpp"
#include "user_interface/plain_text_page_presenter.hpp"
#include "user_interface/title_page_presenter.hpp"

#include "gameplay/danteo_page_request.hpp"

#include "engine/visitor.hpp"

#include "engine/game_runner.hpp"

#include <ftxui/component/screen_interactive.hpp>

#include <array>

namespace danteo {
struct GameFlow {
    GamePresenter<ftxui::ScreenInteractive>& renderer;

    std::optional<size_t> previous = std::nullopt;
    size_t                current  = 0;

    static constexpr std::array<DanteoPageRequest, 2> applicationPages{
        DanteoPageRequest{TitlePage{.title      = "DanteO",
                                    .box_size   = {Width{50U}, Height{10U}},
                                    .box_color  = HSV{0, 255, 30},
                                    .page_color = HSV{0, 0, 10}}},
        DanteoPageRequest{PlainTextPage{"Hello there."}}};

    void doOnNext() { ++current; }

    auto pagePresenter() {
        auto onNext = [this] { doOnNext(); };

        return Visitor{
            [=](TitlePage const& page) -> ftxui::Component { return pageFromTitle(page, onNext); },
            [=](PlainTextPage const& page) -> ftxui::Component { return pageFrom(page, onNext); }};
    }

    bool update([[maybe_unused]] GameClock::Elapsed elapsed) {
        if (!previous || *previous != current) {
            previous = current;
            if (current >= applicationPages.size()) {
                renderer.stopRunning();
                return false;
            }

            renderer.setCurrentPage(applicationPages[current] // NOLINT subscript
                                        .present<ftxui::Component>(pagePresenter()));
        }
        return true;
    };
};

void mainLoop() {
    auto          screen = ftxui::ScreenInteractive::Fullscreen();
    GamePresenter renderer{screen};
    GameRunner    runner{};

    GameFlow flow{renderer};

    std::thread gameThread{[&] {
        static constexpr auto startDelay = std::chrono::milliseconds{100};
        std::this_thread::sleep_for(startDelay);

        runner.run([&](GameClock::Elapsed elapsed) { return flow.update(elapsed); });
    }};
    renderer.runUI();
    gameThread.join();
}
} // namespace danteo
