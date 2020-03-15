#include "stdafx.h"
#include "CCamera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

CCamera::CCamera()
{
	Position = glm::vec3(0.0f, 0.0f, 3.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Direction = glm::normalize(Position - Front);
	Shift = glm::vec3(0);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::normalize(glm::cross(up, Direction));
	Up = glm::cross(Direction, Right);
}

glm::mat4 CCamera::GetView()
{
	return glm::lookAt(Position + Shift,
		Position + Front + Shift,
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void CCamera::Move(EDirection Direction, GLfloat cameraSpeed)
{
	cameraSpeed *= 5;
	switch (Direction)
	{
	case EDirection::Forward:
		Position += cameraSpeed * Front;
		break;
	case EDirection::Back:
		Position -= cameraSpeed * Front;
		break;
	case EDirection::Left:
		Position -= glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
		break;
	case EDirection::Right:
		Position += glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
		break;
	default:
		break;
	}
	//std::cout << Position.x<<' ' << Position.y << ' ' << Position.z << ' ' << std::endl;
}

void CCamera::Rotate(const glm::vec3& Angle)
{
	//glm::vec3 Direction;
	//Direction = glm::normalize(Target - Position);
	//Direction = glm::rotateY(Direction, Angle.y);
	//Target = glm::normalize(Position - Direction);
}

void CCamera::Rotate(GLfloat Yaw, GLfloat Pitch)
{
	m_Yaw += Yaw;
	m_Pitch += Pitch;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	Front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
	Front.y = sin(glm::radians(m_Pitch));
	Front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
	Front = glm::normalize(Front);
}

void CCamera::SetEyePos(EEyePos EyePos)
{
	m_EyePos = EyePos;
	switch (m_EyePos)
	{
	case EEyePos::Normal:
		Shift = glm::vec3(0);
		break;
	case EEyePos::Left:
		Shift = glm::normalize(glm::cross(Front, Up)) * (m_EyeDistance / 2);
		break;
	case EEyePos::Right:
		Shift = -glm::normalize(glm::cross(Front, Up)) * (m_EyeDistance / 2);
		break;
	default:
		break;
	}
}

EEyePos CCamera::GetEyePos() const
{
	return m_EyePos;
}

void CCamera::SetEyeDistance(GLfloat EyeDistance)
{
	m_EyeDistance = std::max(EyeDistance, -0.1f);
	m_EyeDistance = std::min(EyeDistance, 0.1f);
}

GLfloat CCamera::GetEyeDistance() const
{
	return m_EyeDistance;
}
