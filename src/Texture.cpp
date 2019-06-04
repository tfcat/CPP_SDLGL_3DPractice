#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filename)
{
	int width, height, numComponents;
	unsigned char* imageData = 
		stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

	if(imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << filename << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// let the texture wrap around
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// linear filter for the texture!
	
	// GL_LINEAR is linear interpolation, or can GL_NEAREST for pixelly

	// GL_TEXTURE_MIN_FILTER for when the texture being rendered is 
	// fewer pixels than its on-screen resolution
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// GL_TEXTURE_MAG_FILTER for when the texture being rendered is 
	// MORE pixels than its on-screen resolution
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}


void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}