#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();
    ~Window();
    void begin();
    void end();
    bool isOpen();

private:
    GLFWwindow* m_windowHandle;
};
