#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <camera/camera.h>



class Menu {
private:
	bool started = false;

public:
	Camera* camera;

	Menu(Camera* camera);
	void update(GLFWwindow* window);
	bool game_started();

private:
	bool start_clicked();
};
