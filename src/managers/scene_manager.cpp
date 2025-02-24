#include "boson/managers/scene_manager.h"

namespace boson {

SceneManager::SceneManager(const std::string& file_path) {
	std::ifstream file;
	file.open(file_path);

	std::string line;
	json data;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			data = json::parse(line);

			std::cout << data << "\n";
		}
	}



	file.close();
}

SceneManager::~SceneManager()
{
}

}

