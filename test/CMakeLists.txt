find_package(Catch2 REQUIRED)
find_package(fmt REQUIRED)
find_package(Microsoft.GSL REQUIRED)

include(CTest)
include(Catch)


# Provide a simple smoke test to make sure that the CLI works and can display a --help message
add_test(NAME cli.has_help COMMAND danteo --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND danteo --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")


add_library(test_helpers INTERFACE
        format_chrono.hpp)

target_include_directories(test_helpers INTERFACE ".")

add_executable(tests
        catch_main.cpp
        )

add_subdirectory(engine)
add_subdirectory(user_interface)
add_subdirectory(gameplay)

target_link_libraries(tests
        PUBLIC
        Catch2::Catch2
        project_warnings
        project_options
        fmt::fmt
        user_interface_tests
        engine_constexpr_tests
        gameplay_tests)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
        tests
        TEST_PREFIX "unittests."
        REPORTER xml
        OUTPUT_DIR .
        OUTPUT_PREFIX "unittests."
        OUTPUT_SUFFIX .xml)
