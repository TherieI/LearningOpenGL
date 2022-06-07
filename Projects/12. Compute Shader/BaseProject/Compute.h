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
	unsigned int ID;
	unsigned int texture;
	GLenum active_texture;
	ComputeShader(const char* computePath);
	void createTexture(GLenum active_texture, unsigned int width, unsigned int height);
	void setValues(float* values, glm::vec3 dim);
	std::vector<float> getValues(glm::vec3 dim);
	void use();
	void dispatch(glm::vec3 dim);
	void wait();

private:
	void checkCompileErrors(GLuint shader, std::string type);
};
