#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include "FileHandler.h"
#include "Transform.h"

class Shader {
public:
	Shader(const std::string& filename);
	virtual ~Shader();
	void Bind();
	void Update(const Transform& transform);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];	
	GLuint m_uniforms[NUM_UNIFORMS];	
};

static void CheckShaderError
(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

static GLuint CreateShader(const std::string& text, GLenum shaderType);