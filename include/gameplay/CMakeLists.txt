add_library(gameplay_interfaces INTERFACE
        danteo_page_request.hpp
        danteo_state_graph.hpp
        danteo_page_component_factory.hpp
        danteo_update_loop.hpp

        plain_text_page.hpp
        title_page.hpp
        plain_text_page_presenter.hpp
        title_page_presenter.hpp
        )

target_link_libraries(gameplay_interfaces INTERFACE
        engine_interface
        user_interface_core
        ftxui::component
        )
target_include_directories(gameplay_interfaces INTERFACE ${DANTEO_INCLUDE_PATH})
