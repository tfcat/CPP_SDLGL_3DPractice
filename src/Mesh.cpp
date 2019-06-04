#include "Mesh.h"

Mesh::Mesh(Vertex vertices[], unsigned int numVertices)
{
	drawCount = numVertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texcoords;

	positions.reserve(numVertices);
	texcoords.reserve(numVertices);

	for (int i = 0; i < numVertices; ++i)
	{
		positions.push_back(vertices[i].pos);
		texcoords.push_back(vertices[i].texcoord);
	}
	
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	// BUFFER FOR POSITIONS
	// generate blocks of data on the GPU that we can write to
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
	// takes data from ram to GPU memory
	glBufferData(
		GL_ARRAY_BUFFER, 
		numVertices * sizeof(positions[0]), 
		&positions[0],
		// "draw hint", where to put in the GPU
		// static_draw will not be changed. optimisations are done
		// in the gpu depending on the hint!
		GL_STATIC_DRAW);

	// how do we interpret the data once we try to draw it?
	glEnableVertexAttribArray(0);
	// index, size, type, normalise, stride and pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);



	// BUFFER FOR TEXTURE COORDINATES, attribute 1
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(
		GL_ARRAY_BUFFER, 
		numVertices * sizeof(texcoords[0]), 
		&texcoords[0],
		GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayObject);

	// draw triangles, from the start, to the # of vertices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, drawCount);
	
	glBindVertexArray(0);
}