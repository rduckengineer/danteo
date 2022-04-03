add_library(engine_interface INTERFACE
        game_clock.hpp
        )

target_include_directories(engine_interface INTERFACE ${DANTEO_INCLUDE_PATH})
