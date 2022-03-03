#include <glm/glm.hpp>
#include <GL/glew.h>
#include <stdio.h>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

int main() {
	Display display(400, 300, "GL/SDL Practice ft. Kanye West");

	Vertex vertices[] = {
		Vertex(glm::vec3(0, -0.5, 0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1.0, 0)),
		Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(0, 0.5, -0.5), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, 0.5, 0.2), glm::vec2(1.0, 0)),
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
	};

	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./resources/basicShader");
	Texture texture("./resources/lmao.jpg");
	Transform transform;

	float counter = 0.0f;

	while(!display.HasQuit())
	{
		if(display.ShouldNext()){
			display.Clear(1.0f, 0.8f, 0.8f, 1.0f);

			transform.GetRot().y = counter;
			transform.GetRot().x = counter;

			// bind shader -> bind texture -> draw mesh
			shader.Bind();
			texture.Bind(0);
			shader.Update(transform);
			mesh.Draw();

			// draw rectangle
			glUseProgram(0);
			glColor4d(0/255, 0/255, 0/255, 100/255);
			glRectd(-1.0, 0.0, 1.0, 1.0);

			display.Update();

			counter += 0.01f;
		}
	}

    return 0;
}

