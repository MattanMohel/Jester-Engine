#include "Renderer.h"

GLint Renderer::MAX_TEXTURE_SLOTS;

void Renderer::Init()
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_SLOTS);
}

void Renderer::Shutdown()
{

}

void Renderer::AddBuffer()
{

}

void Renderer::Render()
{

}