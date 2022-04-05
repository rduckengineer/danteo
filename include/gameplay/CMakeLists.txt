add_library(gameplay_interfaces INTERFACE
        danteo_page_request.hpp
        )

target_link_libraries(gameplay_interfaces INTERFACE engine_interface user_interface_core)
target_include_directories(gameplay_interfaces INTERFACE ${DANTEO_INCLUDE_PATH})
