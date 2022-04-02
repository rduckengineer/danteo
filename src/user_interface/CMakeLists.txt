# User interface implementations

# Core logic for the UI
add_library(user_interface_core_impl STATIC
        plain_text_page.cpp)

target_link_libraries(
        user_interface_core_impl
        PRIVATE
        project_options
        project_warnings
        PUBLIC
        user_interface_core
)

# Terminal-related display logic
add_library(user_interface_impl STATIC
        plain_text_page_presenter.cpp
        title_page_presenter.cpp)

target_link_libraries(
        user_interface_impl
        PRIVATE
        project_options
        project_warnings
        PUBLIC
        user_interface
        user_interface_core_impl
        ftxui::screen
)
