#include "Application.h"
#include <imgui.h>

Application::Application() {
    m_window = std::make_unique<Window>();
}

void Application::run() {
    while (m_window->isOpen()) {
        m_window->begin();

        ImGui::Begin("Hello, world!");
        ImGui::Button("Hello, world!");
        ImGui::End();

        m_window->end();
    }
}