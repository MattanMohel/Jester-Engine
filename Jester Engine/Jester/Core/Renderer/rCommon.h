#pragma once

#include "../Vector2.h"
#include "../Vector3.h"

#define ToVec3(v) glm::vec3(v.x, v.y, v.z)
#define ToVec3(v, z) glm::vec3(v.x, v.y, z)
#define ToVec2(v) glm::vec2(v.x, v.y)

#define ToVector3(v) Vector3(v.x, v.y, v.z)
#define ToVector2(v) Vector2(v.x, v.y)

#define Deg2Rad 3.14159265f / 180.0f

#define VS_PATH "resources/shaders/vStandart.shader"
#define FS_PATH "resources/shaders/fStandart.shader"

#define Y_AXIS_SORT true

static float VERTICES[] = {
	/*  x val  y val  z val u val v val*/
	/*bl*/	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	/*tl*/	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
	/*tr*/	 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
	/*tl*/	 1.0f, -1.0f, 0.0f, 1.0f, 1.0f
};
static size_t INDICES[] = {
	3, 0, 1,
	1, 2, 3
};