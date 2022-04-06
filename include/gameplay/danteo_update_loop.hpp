#ifndef DANTEO_DANTEO_UPDATE_LOOP_HPP
#define DANTEO_DANTEO_UPDATE_LOOP_HPP

#include "engine/state_machine.hpp"
#include "engine/game_clock.hpp"

#include "user_interface/game_screen.hpp"

#include "gameplay/danteo_state_graph.hpp"
#include "gameplay/danteo_page_per_state.hpp"
#include "gameplay/page_presenter.hpp"

#include <fmt/format.h>

namespace danteo {
struct DanteoNavigation {
    std::optional<State> changeState(std::optional<Event> event) {
        if (!event) { return std::nullopt; }
        return stateMachine.when(*event);
    }

    [[nodiscard]] DanteoPageRequest const& pageRequested() const {
        return pageForState(stateMachine.state());
    }

private:
    [[nodiscard]] DanteoPageRequest const& pageForState(State state) const {

        auto maybePageRequest = requestMap.pageFor(state);
        if (!maybePageRequest) {
            throw std::logic_error{
                fmt::format("There is no page corresponding to the state '{}'", state.name)};
        }
        return *maybePageRequest;
    }

    StateMachine          stateMachine{gameStateGraph(), States::titleScreen};
    StateToPageRequestMap requestMap = pagePerState();
};

struct GameUpdateLoop {
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
    PageComponentFactory pageFactory{[&](Event event) { nextEventToApply = event; }};
    DanteoNavigation     navigation{};
};
} // namespace danteo

#endif // DANTEO_DANTEO_UPDATE_LOOP_HPP
