add_library(gameplay_impl STATIC
        danteo_state_graph.cpp
        danteo_page_presenter.cpp

        pages/title_page_presenter.cpp
        )

target_link_libraries(gameplay_impl
        PRIVATE
        project_options
        project_warnings
        PUBLIC
        gameplay_interfaces
        engine_interface
        user_interface_impl
        )
