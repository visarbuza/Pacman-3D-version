cmake_minimum_required (VERSION 3.14 FATAL_ERROR)
project(Pacman3D VERSION 2.0.0)

# Add dependencies
add_subdirectory(external)

# Create .exe file (essentially)
add_executable(${PROJECT_NAME})

# Find freetype
find_package(Freetype REQUIRED)

add_library(irrKlang SHARED IMPORTED)
if (WIN32)
  set_target_properties(irrKlang PROPERTIES LINKER_LANGUAGE CXX
                                  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/bin/winx64-visualStudio/irrKlang.dll"
                                  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/bin/winx64-visualStudio/ikpMP3.dll"
                                  IMPORTED_IMPLIB   "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/lib/Winx64-visualStudio/irrKlang.lib"
                                  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/include")
endif (WIN32)
if (UNIX)
  set_target_properties(irrKlang PROPERTIES LINKER_LANGUAGE CXX
                                  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/bin/linux-gcc/irrKlang.so"
                                  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/bin/linux-gcc/ikpMP3.so"
                                  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/include")
endif (UNIX)


set_target_properties(irrKlang PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(irrKlang PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


# Add additional source files here
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    # ${CMAKE_CURRENT_LIST_DIR}/include/shader.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/camera.h
    # ${CMAKE_CURRENT_LIST_DIR}/include/model.h
    ${CMAKE_CURRENT_LIST_DIR}/include/text_renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/rendering/text_renderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/level.h
    ${CMAKE_CURRENT_LIST_DIR}/src/level.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/ghost.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ghost.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/route_planner.h
    ${CMAKE_CURRENT_LIST_DIR}/src/ai/route_planner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/food.h
    ${CMAKE_CURRENT_LIST_DIR}/src/food.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/game.h
    ${CMAKE_CURRENT_LIST_DIR}/src/game.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/rendering/model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/texture.h
    ${CMAKE_CURRENT_LIST_DIR}/include/util.h
    ${CMAKE_CURRENT_LIST_DIR}/src/rendering/texture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/config.h
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imconfig.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_glfw.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_internal.h
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui/imgui_widgets.cpp
)

# Set include directories
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${FREETYPE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/bin/winx64-visualStudio
    ${CMAKE_CURRENT_LIST_DIR}/external/irrKlang/include/

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
    tinyobj::tinyobj
    ${FREETYPE_LIBRARIES}

     irrKlang
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

