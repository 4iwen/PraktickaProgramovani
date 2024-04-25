#include "Window.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <cstdio>

Window::Window() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_windowHandle = glfwCreateWindow(1280, 720, "Sit MLM", nullptr, nullptr);
    if (!m_windowHandle) {
        printf("Failed to create window\n");
    }

    glfwMakeContextCurrent(m_windowHandle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    glfwSwapInterval(1);
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_windowHandle);
    glfwTerminate();
}

void Window::begin() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::end() {
    glfwSwapBuffers(m_windowHandle);
    glfwPollEvents();
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(m_windowHandle);
}

void Window::beginUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Window::endUI() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
