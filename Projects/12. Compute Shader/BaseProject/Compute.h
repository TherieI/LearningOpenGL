#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


class ComputeShader {
public:
	unsigned int ID, texture, activeTexture;
	glm::vec2 texDim;
	// A compute shader reading and writing to a texture of size width x height
	ComputeShader(const char* computePath, unsigned int textureWidth, unsigned int textureHeight, unsigned int activeTexture);
	void setValues(float* values, glm::vec3 dim);
	std::vector<float> getValues(glm::vec3 dim);
	void use();
	void dispatch();
	void wait();

private:
	void checkCompileErrors(GLuint shader, std::string type);
};
