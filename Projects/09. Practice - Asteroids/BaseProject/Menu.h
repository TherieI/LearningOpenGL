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
	GameObject asteroid_text = GameObject(
		{
			// Positions          // Texture
			-1.0f, -0.33f,  0.0f,  0.0f, 0.0f, // BL
			 1.0f, -0.33f,  0.0f,  1.0f, 0.0f, // BR
			 1.0f,  0.33f,  0.0f,  1.0f, 1.0f, // TR
			-1.0f,  0.33f,  0.0f,  0.0f, 1.0f, // TL
		},
		{
			0,  1,  2,  // 1st triangle
			0,  2,  3,  // 2nd triangle
		},
		Shader("shaders/button.vs", "shaders/button.fs"),
		Image("assets/title.png", GL_RGBA),
		glm::vec3(0.0f, 0.8f, 7.0f)
	);

	Button play_button = Button(
		{
			// Positions          // Texture
			-1.0f, -0.75f,  0.0f,  0.0f, 0.0f, // BL
			 1.0f, -0.75f,  0.0f,  1.0f, 0.0f, // BR
			 1.0f,  0.75f,  0.0f,  1.0f, 1.0f, // TR
			-1.0f,  0.75f,  0.0f,  0.0f, 1.0f, // TL
		},
		{
			0,  1,  2,  // 1st triangle
			0,  2,  3,  // 2nd triangle
		},
		Shader("shaders/button.vs", "shaders/button.fs"),
		Image("assets/play-purple.png", GL_RGBA),
		glm::vec3(0.5f, -2.5f, 5.0f)
	);

	Menu(Camera* camera);
	void update(GLFWwindow* window, float deltaTime);
	bool game_started();

private:
	bool start_clicked();
};
