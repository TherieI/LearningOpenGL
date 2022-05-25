#include "Menu.h"

Menu::Menu(Camera* camera) {
	this->camera = camera;
}

void Menu::update(GLFWwindow* window) {
	if (start_clicked()) {
		started = true;
	}
}

bool Menu::game_started() {
	return started;
}

bool Menu::start_clicked() {
	return true;
}