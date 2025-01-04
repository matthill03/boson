#pragma once
#include "boson/Window.h"

#include <memory>

namespace boson {
class Application {
public:
    Application(const WindowConfig_t& window_config);
    ~Application();

    void run();

private:
    std::unique_ptr<Window> m_window = nullptr;

};
}
