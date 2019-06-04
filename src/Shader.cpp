#include "Shader.h"

Shader::Shader(const std::string& filename)
{
	// creates space on gpu for our program
	m_program = glCreateProgram();

	// load shaders into m_shaders array
	m_shaders[0] = CreateShader(FileHandler::LoadFile(filename + ".vs"),
		GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(FileHandler::LoadFile(filename + ".fs"),
		GL_FRAGMENT_SHADER);

	// add all of our shaders to the shader program
	for (int i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(m_program, m_shaders[i]);

	// tells opengl what part of data to read...
	// bind attribute 0 to "position"

	// The (1) here refers to 
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	// where we bind the texture coordinate vec2s...
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texcoord");

	// check if shader program links properly
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Program link error: ");

	// check if shader validated properly
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program validation error: ");

	// you can now use m_uniforms[TRANSFORM_U] to access the transform uniform
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	// delete the individual shaders
	for (int i = 0; i < NUM_SHADERS; ++i){
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	// delete it from the gpu
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform)
{
	glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	// if it's 0, ran out of memory or something
	if(shader == 0) std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	// source and compile
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	// check if there are any errors
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
	return shader;
}


static void CheckShaderError
(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	if(isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE) {
		if(isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << "'" << error << "'" << std::endl;
	}
}