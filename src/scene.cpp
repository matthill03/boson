#include "boson/scene.h"

namespace boson {

Scene::Scene(const std::string& file_path) {
	load_scene(file_path);
}

void Scene::load_scene(const std::string& file_path) {
	std::ifstream file;
	file.open(file_path);

	std::string line;
	json data;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			if (line == "") {
				continue;
			}

			data = json::parse(line);

			if (data["type"] == "window") {
				std::cout << "found window\n";
				// WindowConfig -> { width: 1280, height: 720, title: "Hello World", background colour: {1.0f, 0.0f, 0.0f} }

				WindowConfig window_config = {
					(GLint)data["width"],
					(GLint)data["height"],
					std::string(data["title"]),
					{(GLfloat)data["background_colour"]["r"], (GLfloat)data["background_colour"]["g"], (GLfloat)data["background_colour"]["b"]}
				};

				if (m_window == nullptr) {
					m_window = std::make_unique<Window>(window_config);
				}
				else {
					std::cout << "WARNING: Scene -> Window has already been set. Do you mean to reset it?.\n";
				}

			} else if (data["type"] == "camera") {
				std::cout << "found camera\n";

				m_proj_matrix = glm::perspective(glm::radians((GLfloat)data["fov"]), (float)m_window->get_width() / (float)m_window->get_height(), 0.1f, 2000.0f);
				//m_view_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, -20.0f));

				m_view_matrix = glm::lookAt(
					glm::vec3((GLfloat)data["position"]["x"], (GLfloat)data["position"]["y"], (GLfloat)data["position"]["z"]),
					glm::vec3((GLfloat)data["focus_point"]["x"], (GLfloat)data["focus_point"]["y"], (GLfloat)data["focus_point"]["z"]),
					glm::vec3(0.0f, 1.0f, 0.0f)
				);

				m_shader->use();
				m_shader->set_mat4("projection", m_proj_matrix);
				m_shader->set_mat4("view", m_view_matrix);
				m_shader->set_vec3("view_pos", { (GLfloat)data["position"]["x"], (GLfloat)data["position"]["y"], (GLfloat)data["position"]["z"] });
			}
			else if (data["type"] == "shader") {
				std::cout << "found shader\n";

				if (m_shader == nullptr) {
					m_shader = std::make_shared<Shader>(std::string(data["vertex_shader"]), std::string(data["fragment_shader"]));
					m_renderer = std::make_shared<Renderer>(*m_shader);
				}
				else {
					std::cout << "WARNING: Scene -> Scene shader has already been set. Do you mean to overwrite it?\n";
				}
			}
			else if (data["type"] == "texture") {
				std::cout << "found texture\n";
				// Texture diffuse("../resources/diffuse_box.png", TextureType::DIFFUSE);

				auto item = m_textures.find(data["name"]);

				if (item != m_textures.end()) {
					std::cout << "ERROR: Scene -> Texure (" << data["name"] << ") already exists...\n";
					continue;
				}

				TextureType type;
				if (data["texture_type"] == "diffuse") {
					type = TextureType::DIFFUSE;
				}
				else if (data["texture_type"] == "specular") {
					type = TextureType::SPECULAR;
				}
				else {
					std::cout << "ERROR: Scene -> Texure type (" << data["texture_type"] << ") is invalid...\n";
					continue;
				}

				m_textures.insert({data["name"], std::make_shared<Texture>(std::string(data["file_path"]), type)});
			}
			else if (data["type"] == "texture_set") {
				std::cout << "found texture_set\n";
				// std::vector<Texture> box_textures = { diffuse, specular };

				auto item = m_texture_sets.find(data["name"]);

				if (item != m_texture_sets.end()) {
					std::cout << "ERROR: Scene -> Texture set (" << data["name"] << ") already exists...\n";
					continue;
				}

				std::vector<std::shared_ptr<Texture>> new_texture_set = {};

				for (auto texture : data["textures"]) {
					auto item = m_textures.find(texture);

					if (item == m_textures.end()) {
						std::cout << "ERROR: Scene -> Texture (" << texture << ") does not exist...\n";
						continue;
					}

					new_texture_set.push_back(item->second);
				}

				m_texture_sets.insert({ data["name"], new_texture_set });
			}
			else if (data["type"] == "material") {
				std::cout << "found material\n";

				if (data.contains("textures")) {
					auto item = m_texture_sets.find(data["textures"]);

					if (item == m_texture_sets.end()) {
						std::cout << "ERROR: Secne -> Texture set (" << data["textures"] << ") does not exist...\n";
						continue;
					}

					std::shared_ptr<Material> new_material = std::make_shared<Material>();
					new_material->texture_maps = item->second;

					m_materials.insert({ std::string(data["name"]), new_material });
				}
				else {
					std::shared_ptr<Material> new_material = std::make_shared<Material>();
					new_material->ambient = {
						data["ambient"]["r"],
						data["ambient"]["g"],
						data["ambient"]["b"],
					};

					new_material->diffuse = {
						data["diffuse"]["r"],
						data["diffuse"]["g"],
						data["diffuse"]["b"],
					};

					new_material->specular = {
						data["specular"]["r"],
						data["specular"]["g"],
						data["specular"]["b"],
					};

					m_materials.insert({ std::string(data["name"]), new_material });
				}

			}
			else if (data["type"] == "cube") {
				std::cout << "found cube\n";

				if (data.contains("material")) {
					auto item = m_materials.find(data["material"]);
					if (item == m_materials.end()) {
						std::cout << "ERROR: Scene -> Material (" << data["material"] << ") does not exist...\n";
						continue;
					}

					load_cube({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"], data["size"]["z"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.material = *item->second,
						.shininess = item->second->shininess,
					}, m_mesh_manager.get());
				}
				else {
					load_cube({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"], data["size"]["z"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.shininess = 1.0f,
					}, m_mesh_manager.get());
				}

		
			}
			else if (data["type"] == "model") {
				std::cout << "found model\n";

				if (data.contains("material")) {
					auto item = m_materials.find(data["material"]);
					if (item == m_materials.end()) {
						std::cout << "ERROR: Scene -> Material (" << data["material"] << ") does not exist...\n";
						continue;
					}

					load_model({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"], data["size"]["z"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.material = *item->second,
						.file_path = data["file_path"],
					}, m_mesh_manager.get());
				}
				else {
					load_model({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"], data["size"]["z"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.file_path = data["file_path"],
					}, m_mesh_manager.get());
				}
			}
			else if (data["type"] == "plane") {
				std::cout << "found plane\n";

				if (data.contains("material")) {
					auto item = m_materials.find(data["material"]);
					if (item == m_materials.end()) {
						std::cout << "ERROR: Scene -> Material (" << data["material"] << ") does not exist...\n";
						continue;
					}

					load_plane({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.material = *item->second,
						.tile_count_x = data.contains("tile_count") ? (GLfloat)data["tile_count"]["x"] : 1.0f,
						.tile_count_y = data.contains("tile_count") ? (GLfloat)data["tile_count"]["y"] : 1.0f,
					}, m_mesh_manager.get());
				}
				else {
					load_plane({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.size = {data["size"]["x"], data["size"]["y"]},
						.rotation = {data["rotation"]["x"], data["rotation"]["y"], data["rotation"]["z"]},
						.tile_count_x = (data.contains("tile_count")) ? (GLfloat)data["tile_count"]["x"] : 1.0f,
						.tile_count_y = (data.contains("tile_count")) ? (GLfloat)data["tile_count"]["y"] : 1.0f,
					}, m_mesh_manager.get());
				}
			}
			else if (data["type"] == "cylinder") {
				std::cout << "found cylinder\n";
			}
			else if (data["type"] == "sphere") {
				std::cout << "found sphere\n";
			}
			else if (data["type"] == "light") {
				if (m_shader == nullptr) {
					std::cout << "ERROR: Scene -> Unable to set light source due to shader not being set.\n";
					continue;
				}

				std::cout << "found light\n";
				if (data["light_kind"] == "directional") {
					m_light_manager->set_directional_light({
						.direction = {data["direction"]["x"], data["direction"]["y"], data["direction"]["z"]},
						.ambient = {data["ambient"]["r"], data["ambient"]["g"], data["ambient"]["b"]},
						.diffuse = {data["diffuse"]["r"], data["diffuse"]["g"], data["diffuse"]["b"]},
						.specular = {data["specular"]["r"], data["specular"]["g"], data["specular"]["b"]},
					});

					m_shader->use();

					DirectionalLight dir_light = m_light_manager->get_directional_light();
					m_shader->set_vec3("directional_light.direction", dir_light.direction);
					m_shader->set_vec3("directional_light.ambient", dir_light.ambient);
					m_shader->set_vec3("directional_light.diffuse", dir_light.diffuse);
					m_shader->set_vec3("directional_light.specular", dir_light.specular);
				}
				else if (data["light_kind"] == "point") {
					m_light_manager->add_point_light({
						.position = {data["position"]["x"], data["position"]["y"], data["position"]["z"]},
						.constant = data["constant"],
						.linear = data["linear"],
						.quadratic = data["quadratic"],
						.ambient = {data["ambient"]["r"], data["ambient"]["g"], data["ambient"]["b"]},
						.diffuse = {data["diffuse"]["r"], data["diffuse"]["g"], data["diffuse"]["b"]},
						.specular = {data["specular"]["r"], data["specular"]["g"], data["specular"]["b"]},
					});

					m_shader->use();

					std::vector<PointLight> point_lights = m_light_manager->get_point_lights();
					m_shader->set_int("num_point_lights", (GLint)point_lights.size());

					for (int i = 0; i < point_lights.size(); i++) {
						m_shader->set_vec3("point_lights[" + std::to_string(i) + "].position", point_lights[i].position);
						m_shader->set_float("point_lights[" + std::to_string(i) + "].constant", (GLfloat)point_lights[i].constant);
						m_shader->set_float("point_lights[" + std::to_string(i) + "].linear", (GLfloat)point_lights[i].linear);
						m_shader->set_float("point_lights[" + std::to_string(i) + "].quadratic", (GLfloat)point_lights[i].quadratic);
						m_shader->set_vec3("point_lights[" + std::to_string(i) + "].ambient", point_lights[i].ambient);
						m_shader->set_vec3("point_lights[" + std::to_string(i) + "].diffuse", point_lights[i].diffuse);
						m_shader->set_vec3("point_lights[" + std::to_string(i) + "].specular", point_lights[i].specular);
					}
				}
				else {
					std::cout << "ERROR: Scene -> Light kind (" << data["light_kind"] << ") is invalid...\n";
					continue;
				}
			}
			else if (data["type"] == "skybox") {
				std::cout << "found skybox\n";
				
				if (m_skybox != nullptr) {
					std::cout << "WARNING: Scene -> Skybox has already been set. Are you sure you want to overwrite it?\n";
					continue;
				}

				std::vector<std::string> faces = {};

				for (auto face : data["faces"]) {
					faces.push_back(face);
				}

				m_skybox = std::make_shared<Skybox>(faces);
			}
		}
	}

	file.close();
}

void Scene::run() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	double previous_time = glfwGetTime();
	int frame_count = 0;

	while (!glfwWindowShouldClose(m_window->get_handle()))
	{
		glClearColor(m_window->get_colour().x, m_window->get_colour().y, m_window->get_colour().z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double current_time = glfwGetTime();
		frame_count++;

		if (current_time - previous_time >= 1.0) {
			std::cout << "FPS: " << frame_count << "\n";

			frame_count = 0;
			previous_time = current_time;
		}

		m_skybox->draw(m_view_matrix, m_proj_matrix);

		m_shader->use();
		for (const auto& mesh : m_mesh_manager->get_meshes()) {
			m_renderer->draw(*mesh.second);
		}

		glfwSwapBuffers(m_window->get_handle());
		glfwPollEvents();
	}

}

Scene::~Scene()
{
}

}

