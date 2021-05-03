#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>

#include "../Core/Log.h"

enum class Filter
{
	linear = 9729,
	nearest = 9728
};

enum class Wrap
{
	repeat = 10497,
	mirrored_repeat = 33648
};

class Texture
{
public:
	Texture();
	~Texture();

	void LoadTexture();
	void ClearTexture();

	void Bind(GLuint slot);
	static void Unbind(GLuint slot);

	void SetTexture(const std::string& path);

	inline unsigned int GetTextureHashID() const { return m_TextureHashID; }
	inline GLuint GetTextureID() const { return m_TextureID; }

private:
	GLuint m_TextureID;
	int m_Width, m_Height, m_BitDepth;
	GLenum m_WrappingMode, m_FilterMode;

	std::string m_TexturePath;
	unsigned int m_TextureHashID;

	static std::unordered_map<unsigned int, GLuint> textureCache;
};

