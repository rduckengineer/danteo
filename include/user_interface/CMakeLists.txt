add_library(user_interface_core INTERFACE
        plain_text_page.hpp
        title_page.hpp
        size_2d.hpp
        color.hpp
        )

target_include_directories(user_interface_core INTERFACE ${DANTEO_INCLUDE_PATH})

add_library(user_interface_presenters INTERFACE
        plain_text_page_presenter.hpp
        title_page_presenter.hpp
        main_loop.hpp)

target_include_directories(user_interface_presenters INTERFACE ${DANTEO_INCLUDE_PATH})

target_link_libraries(user_interface_presenters INTERFACE
        ftxui::screen
        ftxui::dom
        ftxui::component)


add_library(user_interface INTERFACE)

target_link_libraries(user_interface INTERFACE
        user_interface_core
        user_interface_presenters)
