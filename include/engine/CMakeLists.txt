add_library(engine_interface INTERFACE
        game_clock.hpp
        game_runner.hpp
        page_request.hpp
        visitor.hpp
        )

target_include_directories(engine_interface INTERFACE ${DANTEO_INCLUDE_PATH})
