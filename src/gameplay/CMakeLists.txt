add_library(gameplay_impl STATIC
        main_loop.cpp

        danteo_state_graph.cpp
        danteo_page_presenter.cpp

        pages/title_page_presenter.cpp
        pages/dialogue_page_presenter.cpp
        )

target_link_libraries(gameplay_impl
        PRIVATE
        project_options
        project_warnings
        fmt::fmt
        PUBLIC
        gameplay_interfaces
        engine_impl
        user_interface_impl
        )
