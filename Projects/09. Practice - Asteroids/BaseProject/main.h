#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings.h"
#include "Menu.h"
#include "Game.h"
#include "Ship.h"

enum GameState {
	MENU,
	GAME
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // Handles Window size changes