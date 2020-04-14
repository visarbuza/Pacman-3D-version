# Create library for Tiny Obj Loader

add_library(tinyobj STATIC)
add_library(tinyobj::tinyobj ALIAS tinyobj)

# Add source files
target_sources(
    tinyobj

    # Public Sources
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tiny_obj_loader.h

    # Private Sources
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/tiny_obj_loader.cpp
)

# Set include directories
target_include_directories(
    tinyobj
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
