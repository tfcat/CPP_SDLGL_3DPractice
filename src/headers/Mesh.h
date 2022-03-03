#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <stdio.h>
#include <vector>

// this could be a struct?
class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texcoord) {
		this->pos = pos;
		this->texcoord = texcoord;
	}
	glm::vec2 texcoord;
	glm::vec3 pos;
private:
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();

	void Draw();
private:
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
	unsigned int drawCount;
};