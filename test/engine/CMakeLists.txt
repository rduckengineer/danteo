add_library(engine_constexpr_tests OBJECT
        game_clock_constexpr_test.cpp
        game_runner_test.cpp
        page_request_test.cpp
        state_graph_test.cpp
        state_machine_test.cpp
        )

target_link_libraries(engine_constexpr_tests PUBLIC
        engine_interface
        engine_impl
        test_helpers
        Catch2::Catch2
        project_warnings
        project_options
        fmt::fmt)
