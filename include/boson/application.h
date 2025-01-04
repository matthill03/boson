#pragma once
#include <memory>

#include "boson/window.h"
#include "boson/vertex_array.h"
#include "boson/shader.h"
#include "boson/renderer.h"

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
