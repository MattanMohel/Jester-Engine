#pragma once

#include "GL/glew.h"
#include <vector>
class Sprite;
struct Vertex;

class Renderer
{
public:
	Renderer() = delete;

	static void Init();
	static void Shutdown();

	static void AddSprite(Sprite*);
	static void Render(); 

private:
	static void CreateBuffer();

	static Vertex* vertexBuffer;
	static size_t* indexBuffer;
	static GLint MAX_TEXTURE_SLOTS, MAX_QUADS_PER_DRAW;
	static size_t usedTextureSlots, usedQuads;
	static std::vector<Sprite*> sprites;
	static std::vector<GLuint> usedTextures;
	static GLuint VAO, VBO, IBO;
};

