#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Transform {
public:
	Transform
	(const glm::vec3& pos = glm::vec3(), 
		const glm::vec3& rot = glm::vec3(), 
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	: pos(pos), rot(rot), scale(scale) {}
	
	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMatrix = glm::translate(pos);
		glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1,0,0));
		glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0,1,0));
		glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0,0,1));
		glm::mat4 scaleMatrix = glm::scale(scale);

		// reverse order, x first, then y, then z
		glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& GetPos() { return pos; }
	inline glm::vec3& GetRot() { return rot; }
	inline glm::vec3& GetScale() { return scale; }

	inline glm::vec3& SetPos(const glm::vec3& i_pos) { pos = i_pos; }
	inline glm::vec3& SetRot(const glm::vec3& i_rot) { rot = i_rot; }
	inline glm::vec3& SetScale(const glm::vec3& i_scale) { scale = i_scale; }

protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};