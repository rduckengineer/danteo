add_library(engine_interface INTERFACE
        game_clock.hpp
        game_runner.hpp
        page_request.hpp
        state.hpp
        event.hpp
        state_graph.hpp
        state_graph_builder.hpp
        state_machine.hpp
        page_navigation.hpp
        state_to_page_request_map.hpp
        state_to_page_request_map_builder.hpp
        )

target_include_directories(engine_interface INTERFACE ${DANTEO_INCLUDE_PATH})
