#pragma once

enum class EDirection
{
	Forward,
	Back,
	Left,
	Right
};

enum class EEyePos
{
	Normal,
	Left,
	Right
};

class CCamera
{
private:
	glm::vec3 Position, Front, Right, Up;
	glm::vec3 Shift;
	GLfloat m_Yaw = -90.0f;
	GLfloat m_Pitch = 0.0f;
	EEyePos m_EyePos = EEyePos::Normal;
	GLfloat m_EyeDistance = 0.01f;

public:
	CCamera();
	glm::mat4 GetView();
	void Move(EDirection Direction, GLfloat speed);
	void Rotate(const glm::vec3& Angle);
	void Rotate(GLfloat Yaw, GLfloat Pitch);
	void SetEyePos(EEyePos EyePos);
	EEyePos GetEyePos() const;
	void SetEyeDistance(GLfloat EyeDistance);
	GLfloat GetEyeDistance() const;
};

