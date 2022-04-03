add_library(engine_constexpr_tests STATIC
        game_clock_constexpr_test.cpp
        )

target_link_libraries(engine_constexpr_tests PUBLIC
        engine_interface
        Catch2::Catch2)
