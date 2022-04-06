add_library(engine_interface INTERFACE
        game_clock.hpp
        game_runner.hpp
        page_request.hpp
        visitor.hpp
        state.hpp
        event.hpp
        state_graph.hpp
        state_graph_builder.hpp
        )

target_include_directories(engine_interface INTERFACE ${DANTEO_INCLUDE_PATH})
