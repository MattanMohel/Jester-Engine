#pragma once

#include <string>

#include "../Core/Component.h"
#include "../Core/Gameobject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#define MOVE_SPEED 1000.0f
#define TURN_SPEED 0.75f

#define NEAR_CLIPPING_PLANE 0.1f
#define FAR_CLIPPING_PLANE 100.0f

#define ORTHO_VIEW 1
#define CAMERA_SCALE_FACTOR 1
#define SCALE 500.0f

class Camera : public Component
{
public:
	Camera();

	const char* GetName() override { return "Camera"; }
	void OnUpdate() override;

	glm::mat4 CalculateViewMatrix() const;

	inline float& Size() { return m_Size; }
	inline glm::mat4 GetProjection() const { return m_Projection; }

	glm::mat4 CalculateMVP(Transform& transform);

private:
	glm::mat4 m_Projection;

	glm::vec3 m_Front,
		m_Up, m_Right, m_WorldUp;

	float m_Size;
	float m_Yaw, m_Pitch;
 };

