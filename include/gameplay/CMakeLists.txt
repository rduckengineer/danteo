add_library(gameplay_interfaces INTERFACE
        danteo_page_request.hpp
        danteo_state_graph.hpp
        danteo_page_per_state.hpp
        page_presenter.hpp
        danteo_update_loop.hpp
        )

target_link_libraries(gameplay_interfaces INTERFACE
        engine_interface
        user_interface_core
        ftxui::component
        )
target_include_directories(gameplay_interfaces INTERFACE ${DANTEO_INCLUDE_PATH})
