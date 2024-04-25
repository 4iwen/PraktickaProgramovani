cmake_minimum_required(VERSION 3.6)
project(SitMLM LANGUAGES CXX)

add_executable(
        SitMLM

        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp

        DesktopApp.cpp
        Window.cpp
        Application.cpp
)

target_link_libraries(
        SitMLM PRIVATE

        nlohmann_json::nlohmann_json
        stb
        glfw
        glad
        HTTPRequest
        ws2_32
)

include_directories(
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/glfw/include
        ${CMAKE_SOURCE_DIR}/vendor/glad/include
        ${CMAKE_SOURCE_DIR}/vendor/HTTPRequest/include
        ${CMAKE_SOURCE_DIR}/vendor/imgui
        ${CMAKE_SOURCE_DIR}/vendor/json/include
        ${CMAKE_SOURCE_DIR}/vendor/stb
)
