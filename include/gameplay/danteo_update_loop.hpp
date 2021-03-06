#ifndef DANTEO_DANTEO_UPDATE_LOOP_HPP
#define DANTEO_DANTEO_UPDATE_LOOP_HPP

#include "engine/page_navigation.hpp"
#include "engine/state_to_page_request_map.hpp"
#include "engine/game_clock.hpp"

#include "user_interface/game_screen.hpp"

#include "gameplay/danteo_page_component_factory.hpp"
#include "gameplay/danteo_page_request.hpp"
#include "gameplay/danteo_state_graph.hpp"

namespace danteo {

class GameUpdateLoop {
public:
    explicit GameUpdateLoop(GameScreen<ftxui::ScreenInteractive>& gameScreen)
        : gameScreen_{gameScreen} {}

    void initialize() { updateCurrentPage(navigation.pageRequested()); }

    bool update([[maybe_unused]] engine::GameClock::Elapsed elapsed) {
        auto newState = navigation.changeState(nextEventToApply);
        nextEventToApply.reset();

        if (!newState) {
            return true;
        } else if (*newState == States::exit) {
            gameScreen_.stopRunning();
            return false;
        }

        updateCurrentPage(navigation.pageRequested());

        return true;
    };

private:
    void updateCurrentPage(DanteoPageRequest const& request) {
        gameScreen_.setCurrentPage(pageFactory.makePageAt(request));
    }

    std::optional<engine::Event> nextEventToApply{};

    GameScreen<ftxui::ScreenInteractive>& gameScreen_;
    DanteoPageComponentFactory pageFactory{[&](engine::Event event) { nextEventToApply = event; }};
    engine::PageNavigation<DanteoPageRequest> navigation = gameNavigation();
};
} // namespace danteo

#endif // DANTEO_DANTEO_UPDATE_LOOP_HPP
