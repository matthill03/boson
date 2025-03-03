#pragma once
#include <glad/gl.h>
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

#include "boson/scene.h"


namespace boson {
class Application {
public:
    Application(const std::string& file_path);
    ~Application();

    void run();

private:

    std::unique_ptr<Scene> m_scene = nullptr;

};
}
