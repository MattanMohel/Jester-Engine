#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "RendererBase.h"
#include "../vendors/stb_image.h"

std::unordered_map<unsigned int, GLuint> Texture::textureCache;

Texture::Texture()
	: m_TexturePath(""), m_TextureID(0), m_Height(0), m_Width(0), m_BitDepth(0),
	m_WrappingMode(GL_REPEAT), m_FilterMode(GL_NEAREST), m_TextureHashID(0)
{}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	m_TextureHashID = STR_HASH(m_TexturePath);

	if (textureCache.find(m_TextureHashID) != textureCache.end())
	{
		m_TextureID = textureCache[m_TextureHashID];
		return;
	}

	auto* data = stbi_load(m_TexturePath.c_str(), &m_Width, &m_Height, &m_BitDepth, 0);
	if (!data) Logger::Print(LogFlag::Warning, stbi_failure_reason(), ": ", m_TexturePath);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrappingMode);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	textureCache[m_TextureHashID] = m_TextureID; 
}

void Texture::Bind(GLuint slot)
{
	glBindTextureUnit(slot, m_TextureID);
}

void Texture::Unbind(GLuint slot)
{
	glBindTextureUnit(slot, 0);
}

void Texture::SetTexture(const std::string& path)
{
	m_TexturePath = path;
	LoadTexture();
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &m_TextureID);
	m_Width = m_Height = m_BitDepth = 0;
	m_TexturePath = "";
	m_TextureID = 0;
}