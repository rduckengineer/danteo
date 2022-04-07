add_library(user_interface_core INTERFACE
        size_2d.hpp
        color.hpp
        )

target_include_directories(user_interface_core INTERFACE ${DANTEO_INCLUDE_PATH})

add_library(user_interface_presenters INTERFACE
        game_screen.hpp)

target_include_directories(user_interface_presenters INTERFACE ${DANTEO_INCLUDE_PATH})

target_link_libraries(user_interface_presenters INTERFACE
        ftxui::screen
        ftxui::dom
        ftxui::component)


add_library(user_interface INTERFACE)

target_link_libraries(user_interface INTERFACE
        user_interface_core
        user_interface_presenters)
