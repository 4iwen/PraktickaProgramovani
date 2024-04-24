#pragma once

#include <memory>
#include "Window.h"

class Application {
public:
    Application();

    void run();

private:
    std::unique_ptr<Window> m_window;
};
