#pragma once

#include <string>
#include <GL/glew.h>

#include "../Log.h"

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

	inline bool hasTexture() { return m_HaveTexture; }

	void Bind();
	static void Unbind();

	void SetTexture(const std::string& path);

private:
	GLuint m_TextureID;
	int m_Width, m_Height, m_BitDepth;
	GLenum m_WrappingMode, m_FilterMode;

	std::string m_TexturePath;
	bool m_HaveTexture;
};

