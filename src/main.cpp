#include "user_interface/title_page_presenter.hpp"

#include <docopt/docopt.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

#include <array>
#include <iostream>
#include <fmt/format.h>

#include <internal_use_only/config.hpp>

int main(int argc, const char** argv) {
    try {
        static constexpr auto USAGE =
            R"(danteo

    Usage:
          danteo
          danteo (-h | --help)
          danteo --version
 Options:
          -h --help     Show this screen.
          --version     Show version.
)";

        std::map<std::string, docopt::value> args = docopt::docopt(
            USAGE, {std::next(argv), std::next(argv, argc)},
            true, // show help if requested
            fmt::format("{} {}", danteo::cmake::project_name, danteo::cmake::project_version));

        auto screen = ftxui::ScreenInteractive::Fullscreen();

        constexpr danteo::TitlePage titlePage{.title = "DanteO",
                                              .box_size = {.width = {50}, .height = {10}},
                                              .box_color = danteo::HSV{0, 255, 30},
                                              .page_color = danteo::HSV{0, 0, 10}};

        auto renderer = ftxui::Renderer([&titlePage] { return danteo::present(titlePage); });

        screen.Loop(renderer);

    } catch (const std::exception& e) { fmt::print("Unhandled exception in main: {}", e.what()); }
}
