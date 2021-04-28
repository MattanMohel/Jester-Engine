#include "Camera.h"

#include "../Core/Time.h"
#include "../Core/Input.h"
#include "../Core/Window.h"

#include "RendererBase.h"

Camera::Camera()
	: m_WorldUp(0.0f, 1.0f, 0.0f), m_Yaw(90.0f), m_Pitch(0.0f), m_Front(0.0f, 0.0f, -1.0f), m_Size(5),
	m_Projection(glm::ortho(-WIDTH * m_Size, WIDTH * m_Size, -HEIGHT * m_Size, HEIGHT * m_Size, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE))
{}

glm::mat4 Camera::CalculateViewMatrix() const
{
	glm::vec3 pos = ToVec3(gameobject->transform.position, 0); 
	return glm::lookAt(pos, pos + m_Front, m_Up);
}

void Camera::OnUpdate()
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(m_Front);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	m_Projection = glm::ortho(-WIDTH * m_Size, WIDTH * m_Size,
		-HEIGHT * m_Size, HEIGHT * m_Size, NEAR_CLIPPING_PLANE, FAR_CLIPPING_PLANE);
}
