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

    bool update([[maybe_unused]] GameClock::Elapsed elapsed) {
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

    std::optional<Event> nextEventToApply{};

    GameScreen<ftxui::ScreenInteractive>& gameScreen_;
    DanteoPageComponentFactory        pageFactory{[&](Event event) { nextEventToApply = event; }};
    PageNavigation<DanteoPageRequest> navigation{
        StateMachine{gameStateGraph(), States::titleScreen}, pagePerState()};
};
} // namespace danteo

#endif // DANTEO_DANTEO_UPDATE_LOOP_HPP
