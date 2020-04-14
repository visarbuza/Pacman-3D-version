set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "/home/visar/Documents/NTNU/Courses/Graphics Programming/Exercise/Camera/build/_deps/glm_external-src")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
