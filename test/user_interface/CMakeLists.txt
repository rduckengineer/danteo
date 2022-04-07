add_library(user_interface_tests OBJECT
        color_constexpr_test.cpp
        size_2d_constexpr_test.cpp
        game_screen_test.cpp
        fake_interactive_screen.hpp
        )

target_link_libraries(user_interface_tests
        PRIVATE
        Catch2::Catch2
        ftxui::component
        project_warnings
        project_options
        user_interface_impl)
