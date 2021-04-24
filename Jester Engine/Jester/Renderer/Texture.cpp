#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"
#include "vendor/stb_image.h"

Texture::Texture()
	: m_TexturePath(""), m_TextureID(0), m_Height(0), m_Width(0), m_BitDepth(0),
	m_WrappingMode(GL_REPEAT), m_FilterMode(GL_NEAREST)
{}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	unsigned char* data = stbi_load(m_TexturePath.c_str(), &m_Width, &m_Height, &m_BitDepth, 0);
	if (!data)
		Logger::Print(LogFlag::Warning, stbi_failure_reason(), ": ", m_TexturePath);

	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	glEnable(GL_BLEND);
	/*glDepthFunc(GL_ALWAYS); glDepthFunc(GL_LESS)*/
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMode);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
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