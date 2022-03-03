#pragma once

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <cassert>

class Texture {
public:
	Texture(const std::string& filename);
	~Texture();

	// set up OpenGL to start using whatever texture you're binding
	// unit from 0-31, you can bind up to 32 textures at once!
	// unit will be the determinant for which texture is which
	void Bind(unsigned int unit);
private:
	GLuint m_texture;
};