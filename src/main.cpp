#include "gameplay/main_loop.hpp"

#include <docopt/docopt.h>

#include <array>
#include <iostream>
#include <fmt/format.h>

#include <internal_use_only/config.hpp>

void handleCommandLineParameters(int argc, const char* const* argv);

int main(int argc, const char** argv) {
    try {
        handleCommandLineParameters(argc, argv);
        danteo::mainLoop();
    } catch (const std::exception& e) { fmt::print("Unhandled exception in main: {}", e.what()); }
}

void handleCommandLineParameters(int argc, const char* const* argv) {
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

    [[maybe_unused]] std::map<std::string, docopt::value> args = docopt::docopt(
        USAGE, {std::next(argv), std::next(argv, argc)},
        true, // show help if requested
        fmt::format("{} {}", danteo::cmake::project_name, danteo::cmake::project_version));
}
