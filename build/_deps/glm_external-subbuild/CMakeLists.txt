# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.14.0)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(glm_external-populate NONE)

include(ExternalProject)
ExternalProject_Add(glm_external-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/g-truc/glm.git" "GIT_TAG" "9749727c2db4742369219e1d452f43e918734b4e" "GIT_PROGRESS" "TRUE"
                    SOURCE_DIR          "/home/visar/Documents/NTNU/Courses/Graphics Programming/Exercise/Camera/build/_deps/glm_external-src"
                    BINARY_DIR          "/home/visar/Documents/NTNU/Courses/Graphics Programming/Exercise/Camera/build/_deps/glm_external-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
