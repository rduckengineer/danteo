add_library(user_interface_core INTERFACE
        plain_text_page.hpp
        title_page.hpp)

target_include_directories(user_interface_core INTERFACE ${DANTEO_INCLUDE_PATH})

add_library(user_interface_presenters INTERFACE
        plain_text_page_presenter.hpp
        title_page_presenter.hpp)

target_include_directories(user_interface_presenters INTERFACE ${DANTEO_INCLUDE_PATH})

add_library(user_interface INTERFACE)

target_link_libraries(user_interface_presenters INTERFACE
        ftxui::screen
        ftxui::dom
        ftxui::component)

target_link_libraries(user_interface INTERFACE
        user_interface_core
        user_interface_presenters)
