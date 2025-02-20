#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <string>

namespace boson {

    class SceneManager {

    public:
        SceneManager(const std::string& file_path);
        ~SceneManager();


    private:
    };

}
