find_package(Microsoft.GSL REQUIRED)

add_library(gameplay_impl STATIC
        main_loop.cpp

        danteo_state_graph.cpp
        danteo_page_presenter.cpp

        pages/title_page_presenter.cpp
        pages/dialogue_page_component_base.hpp
        pages/dialogue_page_with_choice_presenter.cpp
        pages/dialogue_page_only_presenter.cpp
        pages/scene_change_page_presenter.cpp

        scenes/scene.hpp

        scenes/ceo_scene.hpp
        scenes/what_is_dantio.hpp
        scenes/what_is_dantio_graph.cpp
        scenes/what_is_dantio_pages.cpp

        scenes/office_space_scene.hpp
        scenes/office_space_scene_graph.cpp
        scenes/office_space_scene_pages.cpp

        scenes/reboot_scene.hpp
        scenes/reboot_scene.cpp
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
