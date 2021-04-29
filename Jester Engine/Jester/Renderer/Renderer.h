#pragma once

#include "GL/glew.h"

class Renderer
{
public:
	Renderer() = delete;

	static void Init();
	static void Shutdown();
	/*should accept: a Transform, a Vertex Buffer, a Index Buffer, a Color, a Texture, a Shader*/
	/*Each sprite passed will have a SORTING_LAYER/ORDER, once you have all the sprites, in render, 
	you order them, or maybe order them as they come in*/
	static void AddBuffer(/*make all things that render inherit from a base?*/);
	static void Render();

	static GLint MAX_TEXTURE_SLOTS;
};

