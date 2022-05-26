#include "Menu.h"

Menu::Menu(Camera* camera) {
	this->camera = camera;

}

void Menu::update(GLFWwindow* window, float deltaTime) {
	if (start_clicked()) {
		started = true;
	}

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(Settings::FOV, (float)Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

	start_button.update(window, camera, model, view, projection);
	start_button.draw();
}

bool Menu::game_started() {
	return started;
}

bool Menu::start_clicked() {
	return false;
}