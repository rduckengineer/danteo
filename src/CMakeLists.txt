find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)

# Generic test that uses conan libs
add_executable(danteo main.cpp)
target_link_libraries(
        danteo
        PRIVATE
        project_options
        project_warnings
        docopt::docopt
        fmt::fmt
        user_interface_impl
        engine_impl
        gameplay_impl
)

target_link_system_libraries(
        danteo
        PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component)

target_include_directories(danteo PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

add_subdirectory(engine)
add_subdirectory(user_interface)
add_subdirectory(gameplay)
