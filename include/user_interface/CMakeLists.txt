add_library(user_interface INTERFACE
        plain_text_page.hpp)

target_include_directories(user_interface INTERFACE ${DANTEO_INCLUDE_PATH})