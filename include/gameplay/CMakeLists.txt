add_library(gameplay_interfaces INTERFACE
        main_loop.hpp

        danteo_page_request.hpp
        danteo_state_to_page_map.hpp
        danteo_state_graph.hpp
        danteo_page_component_factory.hpp
        danteo_update_loop.hpp

        pages/fade_presenter_base.hpp
        pages/title_page.hpp
        pages/title_page_presenter.hpp
        pages/scene_change_page.hpp
        pages/scene_change_page_presenter.hpp
        pages/dialogue_page.hpp
        pages/dialogue_page_builder.hpp
        pages/dialogue_page_presenter.hpp
        )

target_link_libraries(gameplay_interfaces INTERFACE
        engine_interface
        user_interface_core
        project_options
        project_warnings
        ftxui::component
        range-v3::range-v3
        )
target_include_directories(gameplay_interfaces INTERFACE ${DANTEO_INCLUDE_PATH})
