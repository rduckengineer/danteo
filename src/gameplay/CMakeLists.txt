find_package(Microsoft.GSL REQUIRED)

add_library(gameplay_impl STATIC
        main_loop.cpp

        danteo_state_graph.cpp
        danteo_page_presenter.cpp

        pages/title_page_presenter.cpp
        pages/dialogue_page_presenter.cpp
        pages/scene_change_page_presenter.cpp

        scenes/ceo_scene.hpp
        scenes/what_is_dantio.hpp
        scenes/what_is_dantio_graph.cpp
        scenes/what_is_dantio_pages.cpp
        )

target_link_libraries(gameplay_impl
        PRIVATE
        project_options
        project_warnings
        fmt::fmt
        range-v3::range-v3
        PUBLIC
        gameplay_interfaces
        engine_impl
        user_interface_impl
        Microsoft.GSL::GSL
        )
