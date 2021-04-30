#pragma once

#include "GL/glew.h"
#include <vector>
class Sprite;

#define FLOATS_PER_VERTEX 10

class Renderer
{
public:
	Renderer() = delete;

	static void Init();
	static void Shutdown();
	/*should accept: a Transform, a Vertex Buffer, a Index Buffer, a Color, a Texture, a Shader*/
	/*Each sprite passed will have a SORTING_LAYER/ORDER, once you have all the sprites, in render, 
	you order them, or maybe order them as they come in*/
	static void Render();
	static void AddSprite(Sprite*);

private:
	static void CreateBuffer();

	static GLint MAX_TEXTURE_SLOTS;
	static size_t remainingTextureSlots;
	static std::vector<Sprite*> sprites;
};

