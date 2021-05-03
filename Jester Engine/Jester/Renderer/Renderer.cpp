#include "Renderer.h"
#include "Sprite.h"

#include "../Core/Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 uvCoords;
	glm::vec4 color;
	float textureIndex;
	glm::mat4 MVP;
};

Vertex* Renderer::vertexBuffer;
size_t* Renderer::indexBuffer;
GLint Renderer::MAX_TEXTURE_SLOTS;
GLint Renderer::MAX_QUADS_PER_DRAW = 1000;
size_t Renderer::usedQuads;
size_t Renderer::usedTextureSlots;
std::vector<Sprite*> Renderer::sprites;
std::vector<GLuint> Renderer::usedTextures;
GLuint Renderer::VAO;
GLuint Renderer::VBO;
GLuint Renderer::IBO;

// projection * view * model * vec4(pos, 1.0f);

void Renderer::Init()
{
	/*OpenGL Initialization*/
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST); glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vertexBuffer = new Vertex[MAX_QUADS_PER_DRAW * 4]; 
	indexBuffer = new size_t[MAX_QUADS_PER_DRAW * 6];
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_SLOTS);
	usedTextureSlots = usedQuads = 0;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

#pragma region Vertex Attributes
	/*Position Vertex Attribute*/
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));

	/*UV Corrdinates Vertex Attribute*/
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, uvCoords));

	/*Color Vertex Attribute - Per Quad*/
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));	
	
	/*Texture Index Vertex Attribute - Per Quad*/
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, textureIndex));

	/*Model View Projection Vertex Attribute - Per Quad*/
	/*Row 1*/ glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, MVP) + (4 * sizeof(float)) * 0));

	/*Row 2*/ glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, MVP) + (4 * sizeof(float)) * 1));

	/*Row 3*/ glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, MVP) + (4 * sizeof(float)) * 2));

	/*Row 4*/ glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(offsetof(Vertex, MVP) + (4 * sizeof(float)) * 3));
#pragma endregion 
}

void Renderer::Shutdown()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
	delete[] vertexBuffer, indexBuffer;
}

void Renderer::AddSprite(Sprite* sprite)
{
	bool repeatedTexture = false, placed = false;

	for (size_t i = 0; i <= sprites.size(); i++)
	{
		if (!placed && i == sprites.size())
		{
			sprites.push_back(sprite);
			break;
		}

		if (!repeatedTexture && sprite->m_Texture.GetTextureHashID() == sprites[i]->m_Texture.GetTextureHashID())
			repeatedTexture = true;

		if (!placed && ((int)sprite->sortingLayer > (int)sprites[i]->sortingLayer ||
			((int)sprite->sortingLayer == (int)sprites[i]->sortingLayer && sprite->orderInLayer >= sprites[i]->orderInLayer)))
		{
			sprites.insert(sprites.begin() + i, sprite);
			placed = true;
		}
	}

	usedQuads++;
	if (!repeatedTexture)
		usedTextureSlots++;
	if (usedQuads == MAX_QUADS_PER_DRAW || usedTextureSlots == MAX_TEXTURE_SLOTS - 1)
		Render();
}


void Renderer::Render()
{
	if (sprites.size() == 0) return;

	CreateBuffer();
	sprites[0]->m_Shader.Bind();
	glDrawElements(GL_TRIANGLES, 6 * sprites.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	Shader::Unbind();

	usedQuads = 0;
	usedTextureSlots = 0;
	usedTextures.clear();
	sprites.clear();
}


void Renderer::CreateBuffer()
{
	size_t textureIndex = 0;
	memset(vertexBuffer, 0, MAX_QUADS_PER_DRAW * 4);
	memset(indexBuffer, 0, MAX_QUADS_PER_DRAW * 6);

	for (size_t i = 0; i < sprites.size(); i++)
	{
		/*bind texture ID to slot, assign slot*/
		if (std::find(usedTextures.begin(), usedTextures.end(), sprites[i]->m_Texture.GetTextureID()) == usedTextures.end())
		{
			usedTextures.push_back(sprites[i]->m_Texture.GetTextureID());
			sprites[i]->m_Texture.Bind(i);
			textureIndex++;
		}

		/*Calculate Sprite's Model-View Projection*/
		glm::mat4 mvp = sprites[i]->m_Camera->CalculateMVP(sprites[i]->gameobject->transform);
		/*Get Sprite Color*/
		glm::vec4 color = { sprites[i]->color.r, sprites[i]->color.g, sprites[i]->color.b, sprites[i]->color.a };

		vertexBuffer[(i * 4) + 0].position = { -1.0f, -1.0f, 0.0f };
		vertexBuffer[(i * 4) + 0].uvCoords = { 0.0f, 1.0f };
		vertexBuffer[(i * 4) + 0].color = color;
		vertexBuffer[(i * 4) + 0].textureIndex = textureIndex;
		vertexBuffer[(i * 4) + 0].MVP = mvp;
		
		vertexBuffer[(i * 4) + 1].position = { -1.0f,  1.0f, 0.0f };
		vertexBuffer[(i * 4) + 1].uvCoords = { 0.0f, 0.0f };
		vertexBuffer[(i * 4) + 1].color = color;
		vertexBuffer[(i * 4) + 1].textureIndex = textureIndex;
		vertexBuffer[(i * 4) + 1].MVP = mvp;		
		
		vertexBuffer[(i * 4) + 2].position = {  1.0f,  1.0f, 0.0f };
		vertexBuffer[(i * 4) + 2].uvCoords = { 1.0f, 1.0f };
		vertexBuffer[(i * 4) + 2].color = color;
		vertexBuffer[(i * 4) + 2].textureIndex = textureIndex;
		vertexBuffer[(i * 4) + 2].MVP = mvp;		
		
		vertexBuffer[(i * 4) + 3].position = {  1.0f, -1.0f, 0.0f };
		vertexBuffer[(i * 4) + 3].uvCoords = { 1.0f, 1.0f };
		vertexBuffer[(i * 4) + 3].color = color;
		vertexBuffer[(i * 4) + 3].textureIndex = textureIndex;
		vertexBuffer[(i * 4) + 3].MVP = mvp;

		indexBuffer[(i * 6) + 0] = (i * 6) + 3;
		indexBuffer[(i * 6) + 1] = (i * 6) + 0;
		indexBuffer[(i * 6) + 2] = (i * 6) + 1;
		indexBuffer[(i * 6) + 3] = (i * 6) + 1;
		indexBuffer[(i * 6) + 4] = (i * 6) + 2;
		indexBuffer[(i * 6) + 5] = (i * 6) + 3;
	}

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * sprites.size() * 4, vertexBuffer, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sprites.size(), vertexBuffer, GL_STATIC_DRAW);
}

