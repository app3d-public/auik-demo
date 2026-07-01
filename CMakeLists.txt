cmake_minimum_required(VERSION 3.17)

if(NOT DEFINED ACBT_PROJECT_LOADED)
    include(cmake/project.cmake)
endif()

project(auik-demo
    VERSION 0.0.1
    LANGUAGES CXX C
    DESCRIPTION "Auik Demo")

if(NOT DEFINED ACBT_LOADED)
    include(cmake/utils.cmake)
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/../auik/tools/theme_build.cmake")

create_symbol_export_file()
set(AUIK_DEMO_CSS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/style")
set(AUIK_DEMO_THEME "${AUIK_DEMO_CSS_DIR}/theme.css")

compile_auik_style_ids("${AUIK_DEMO_THEME}"
    IDS_CSV "${AUIK_DEMO_CSS_DIR}/style_tags_id.csv"
    IDS_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/auik/demo_style_tags.hpp"
    TARGET_NAME "auik_demo_style_ids"
)

add_files(${PROJECT_NAME} RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/src")
list(APPEND AUIK_DEMO_SRC ${AUIK_STYLE_IDS_HEADER})
add_library(${PROJECT_NAME} SHARED ${AUIK_DEMO_SRC})
add_dependencies(${PROJECT_NAME} ${AUIK_STYLE_IDS_TARGET})

set_target_properties(${PROJECT_NAME} PROPERTIES
    DEFINE_SYMBOL AUIK_DEMO_BUILD
    CXX_VISIBILITY_PRESET hidden
)

target_link_libraries(${PROJECT_NAME} PUBLIC auik)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${AUIK_STYLE_IDS_INCLUDE_DIR}"
    "${AUIK_DEMO_CONFIGURE_PATH}"
)

if(WIN32)
    gen_manifest_lib(lib${PROJECT_NAME} ${PROJECT_VERSION})
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_EXTENSIONS YES
)

get_directory_property(AUIK_DEMO_HAS_PARENT PARENT_DIRECTORY)
if(AUIK_DEMO_HAS_PARENT)
    set(AUIK_DEMO_CSS_DIR "${AUIK_DEMO_CSS_DIR}" PARENT_SCOPE)
endif()
