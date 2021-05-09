#include "Renderer.h"

#include "Sprite.h"

GLint Renderer::MAX_TEXTURE_SLOTS;
size_t Renderer::remainingTextureSlots;
std::vector<Sprite*> Renderer::sprites;

void Renderer::Init()
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_SLOTS);
	remainingTextureSlots = MAX_TEXTURE_SLOTS;
}

void Renderer::Shutdown()
{

}

void Renderer::Render()
{

}

void Renderer::AddSprite(Sprite* sprite)
{
	bool repeatedTexture = false, placed = false;
	/*one check one not? then if suddenly its greater check the one before?
	Maybe do it async/threading? Also later make sure they use the same shaders*/
	for (size_t i = 0; i < sprites.size(); i++)
	{
		if (!repeatedTexture && sprite->m_Texture.GetTextureHashID() == sprites[i]->m_Texture.GetTextureHashID())
			repeatedTexture = true; 

		if (!placed && ((int)sprite->sortingLayer > (int)sprites[i]->sortingLayer || i == sprites.size() - 1 ||
			((int)sprite->sortingLayer == (int)sprites[i]->sortingLayer && sprite->orderInLayer >= sprites[i]->orderInLayer)))
		{
			sprites.insert(sprites.begin() + i, sprite);
			placed = true;
		}
	}

	if (!repeatedTexture)
	{
		remainingTextureSlots--;
		if (remainingTextureSlots == 0)
			Render();
	}
}

void Renderer::CreateBuffer()
{
	remainingTextureSlots = MAX_TEXTURE_SLOTS;
	
	float* VB = new float[sprites.size() * FLOATS_PER_VERTEX];
	/* xpos, ypos, xscale, yscale, zrot, Color(r, g, b, a), textureIndex*/

	for (size_t i = 0; i < sprites.size(); i++)
	{
		VB[i + 0] = sprites[i]->object->transform.position.x;
		VB[i + 1] = sprites[i]->object->transform.position.y;
		VB[i + 2] = sprites[i]->object->transform.scale.x;
		VB[i + 3] = sprites[i]->object->transform.scale.y;
		VB[i + 4] = sprites[i]->object->transform.rotation;
		VB[i + 5] = sprites[i]->color.r;
		VB[i + 6] = sprites[i]->color.g;
		VB[i + 7] = sprites[i]->color.b;
		VB[i + 8] = sprites[i]->color.a;
		VB[i + 9] = sprites[i]->m_Texture.GetTextureID();
	}

	sprites.clear();
}