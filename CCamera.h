#pragma once

enum class EDirection
{
	Forward,
	Back,
	Left,
	Right
};

class CCamera
{
private:
	glm::vec3 Position, Front, Right, Up;
	GLfloat m_Yaw = -90.0f;
	GLfloat m_Pitch = 0.0f;
public:
	CCamera();
	glm::mat4 GetView();
	void Move(EDirection Direction, GLfloat speed);
	void Rotate(const glm::vec3& Angle);
	void Rotate(GLfloat Yaw, GLfloat Pitch);
};

