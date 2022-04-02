
# User interface library
add_library(user_interface_impl STATIC
        plain_text_page.cpp)

target_link_libraries(user_interface_impl PUBLIC user_interface)

target_link_libraries(
        user_interface_impl
        PRIVATE
        project_options
        project_warnings
)