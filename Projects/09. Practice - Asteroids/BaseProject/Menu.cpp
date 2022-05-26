#include "Menu.h"

Menu::Menu(Camera* camera) {
	this->camera = camera;

}

void Menu::update(GLFWwindow* window, float deltaTime) {
	if (start_clicked()) {
		started = true;
	}

	title.update(camera, deltaTime);
    title.draw();
}

bool Menu::game_started() {
	return started;
}

bool Menu::start_clicked() {
	return false;
}