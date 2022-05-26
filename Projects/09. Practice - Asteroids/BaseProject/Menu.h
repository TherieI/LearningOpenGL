#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera/camera.h>

#include "GameObject.h"
#include "Button.h"



class Menu {
private:
	bool started = false;

public:
	Camera* camera;
	Button start_button = Button(
		glm::vec3(0.0f, 0.0f, Settings::ENTITY_DEPTH),
		Shader("shaders/button.vs", "shaders/button.fs"),
		Image("title.png", GL_RGBA)
	);

	Menu(Camera* camera);
	void update(GLFWwindow* window, float deltaTime);
	bool game_started();

private:
	bool start_clicked();
};
