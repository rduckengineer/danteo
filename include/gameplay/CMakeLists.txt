add_library(gameplay_interfaces INTERFACE
        main_loop.hpp

        danteo_page_request.hpp
        danteo_state_graph.hpp
        danteo_page_component_factory.hpp
        danteo_update_loop.hpp

        pages/title_page.hpp
        pages/title_page_presenter.hpp
        pages/plain_text_page.hpp
        pages/plain_text_page_presenter.hpp
        pages/dialogue_page.hpp
        pages/dialogue_page_presenter.hpp
        )

target_link_libraries(gameplay_interfaces INTERFACE
        engine_interface
        user_interface_core
        ftxui::component
        )
target_include_directories(gameplay_interfaces INTERFACE ${DANTEO_INCLUDE_PATH})
