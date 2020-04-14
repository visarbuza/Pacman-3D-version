cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(Graphics VERSION 2.0.0)

# Add dependencies
add_subdirectory(external)

# Create .exe file (essentially)
add_executable(${PROJECT_NAME})

# Add additional source files here
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include/shader.h
    ${CMAKE_CURRENT_LIST_DIR}/include/camera.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
)

# Set include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# Link with external libraries
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    glad::glad
    gfx::gfx
    glm
    glfw
    stbimage::stbimage
)

# Enable C++ 17
target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_17
)

# Copy resources to binary directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E echo "Copied resource directory to binary directory."
)

