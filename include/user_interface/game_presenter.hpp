#ifndef DANTEO_GAME_PRESENTER_HPP
#define DANTEO_GAME_PRESENTER_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

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

}

#endif // DANTEO_GAME_PRESENTER_HPP
