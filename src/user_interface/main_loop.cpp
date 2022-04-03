#include "user_interface/main_loop.hpp"

#include "user_interface/title_page_presenter.hpp"
#include "user_interface/next_component.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace danteo {
void mainLoop() {
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    constexpr danteo::TitlePage titlePage{
        .title = "DanteO",
        .box_size = {Width{50U}, Height{10U}},
        .box_color = danteo::HSV{0, 255, 30},
        .page_color = danteo::HSV{0, 0, 10}};

    auto next = danteo::makeNextComponent(screen.ExitLoopClosure());

    auto renderer = ftxui::Renderer(next, [&titlePage] { return danteo::present(titlePage); });

    screen.Loop(renderer);
}
} // namespace danteo
