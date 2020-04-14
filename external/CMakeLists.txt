# Add dependencies
add_subdirectory(glad)
add_subdirectory(gfx)
add_subdirectory(stb)
add_subdirectory(tiny_obj_loader)
include(${CMAKE_CURRENT_LIST_DIR}/glfw.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/glm.cmake)

# Set FC to be disconnected so we stop downloading
set(FETCHCONTENT_FULLY_DISCONNECTED ON CACHE BOOL "This has been reset to ON (set to OFF to download again)" FORCE)
