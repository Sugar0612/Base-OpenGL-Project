#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <string>
#include <iostream>
#include "stb_image.h"

using namespace::std;


void _Create_Texture(unsigned int &texture, const char *file, string file__type) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height, nrchannels;
	stbi_set_flip_vertically_on_load(true);  // ·­×ª

	unsigned char *data = stbi_load(file, &width, &height, &nrchannels, 0);
	if (data) {
		if (file__type == "png") {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else {
		cout << "failed open image!" << endl;
	}

	//free
	stbi_image_free(data);
}

