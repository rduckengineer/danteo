add_library(engine_impl STATIC
        state_graph.cpp
        )

target_link_libraries(
        engine_impl
        PRIVATE
        project_options
        project_warnings
        PUBLIC
        engine_interface
)
