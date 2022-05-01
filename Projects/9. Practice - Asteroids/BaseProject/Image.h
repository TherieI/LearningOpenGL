#pragma once
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Image {
public:
	unsigned int textureID;

	Image();
	Image(const char* image_location, GLenum type);

	void use();
};