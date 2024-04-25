cmake_minimum_required(VERSION 3.6)
project(PraktickaProgramovani)

# cmake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# dependencies
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/json) # JSON
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glfw) # Windowing
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad) # Rendering
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/HTTPRequest) # Requests
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/stb) # Images & other stuff

# main projects
add_subdirectory(SitMLM)