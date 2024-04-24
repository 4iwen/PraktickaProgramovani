cmake_minimum_required(VERSION 3.6)
project(QR LANGUAGES CXX)

add_executable(
        ${PROJECT_NAME}

        QR.cpp
)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE

        nlohmann_json::nlohmann_json
        stb
        glfw
        glad
        HTTPRequest
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
