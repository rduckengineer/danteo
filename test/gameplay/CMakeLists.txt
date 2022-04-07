add_library(gameplay_tests OBJECT
        plain_text_page_constexpr_test.cpp
        plain_text_page_test.cpp
        title_page_constexpr_test.cpp
        dialogue_page_test.cpp
        )

target_link_libraries(gameplay_tests PUBLIC
        gameplay_interfaces
        gameplay_impl
        test_helpers
        Catch2::Catch2
        project_warnings
        project_options
        fmt::fmt)
