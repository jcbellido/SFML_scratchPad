#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 2.6)

project(SFML_scratchPad)

set(REQUIRED_SFML_MODULES
  network
  audio
  graphics
  window
  system
)

add_definitions("-std=c++11")

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

set(ENV{SFML_ROOT_DIR} "${CMAKE_CURRENT_LIST_DIR}/sfml")
set(ENV{SFML_BUILD_DIR} "${CMAKE_CURRENT_LIST_DIR}/sfml_build")

set(PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")
set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}")
set(PROJECT_RESOURCE_DIR "${PROJECT_SOURCE_DIR}/resources")

# Set version information in a config.h file
set(SFML_scratchPad_VERSION_MAJOR 1)
set(SFML_scratchPad_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

# Define sources and executable
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB MAC_SRC "${PROJECT_SOURCE_DIR}/*.mm")
set(SOURCES ${SOURCES} ${PROJECT_RESOURCE_DIR} ${MAC_SRC})
add_executable(${PROJECT_NAME} ${SOURCES})

# Adding MAC stuff
if(APPLE)
  message("ALAAAAAAAARM IF APPLE")
  target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
endif()

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML REQUIRED ${REQUIRED_SFML_MODULES})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}) 
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${PROJECT_SOURCE_DIR}/resources
                    ${PROJECT_BINARY_DIR}/resources)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${PROJECT_NAME} m)  # if you use maths.h
endif()

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${SFML_scratchPad_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SFML_scratchPad_VERSION_MINOR}")
include(CPack)