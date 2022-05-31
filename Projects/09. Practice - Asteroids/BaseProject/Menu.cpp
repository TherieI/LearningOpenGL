#include "Menu.h"

Menu::Menu(Camera* camera) {
	this->camera = camera;

}

void Menu::update(GLFWwindow* window, float deltaTime) {
	if (start_clicked()) {
		started = true;
	}

	// -------------- Start button ----------------------
	glm::mat4 play_model = glm::mat4(1.0f);
	glm::mat4 play_view = camera->GetViewMatrix();
	glm::mat4 play_projection = glm::perspective(Settings::FOV, (float)Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

	play_button.update(window, play_model, play_view, play_projection);
	play_button.draw();

	if (play_button.is_pressed()) {
		std::cout << "gaming";
	}
	// -------------- Start button ----------------------

	// -------------- asteroid text ----------------------
	glm::mat4 atext_model = glm::mat4(1.0f);
	glm::mat4 atext_view = camera->GetViewMatrix();
	glm::mat4 atext_projection = glm::perspective(Settings::FOV, (float)Settings::WIDTH / Settings::HEIGHT, 0.1f, 100.0f);  // projection remains the same for all cubes

	asteroid_text.position.z += sin(glfwGetTime()) / 100.0f;
	asteroid_text.update(atext_model, atext_view, atext_projection);
	asteroid_text.draw();
	// -------------- asteroid text ----------------------
}

bool Menu::game_started() {
	return started;
}

bool Menu::start_clicked() {
	return false;
}