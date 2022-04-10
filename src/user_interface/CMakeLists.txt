# User interface implementations

# Core logic for the UI
add_library(user_interface_core_impl INTERFACE)

target_link_libraries(
        user_interface_core_impl
        INTERFACE
        user_interface_core
)

# Terminal-related display logic
add_library(user_interface_impl STATIC
        scroller.cpp
        )

target_link_libraries(
        user_interface_impl
        PUBLIC
        user_interface
        user_interface_core_impl
        engine_interface
        ftxui::screen
)
