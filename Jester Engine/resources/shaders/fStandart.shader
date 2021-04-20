#version 330

in vec4 Color;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D mainTex;
uniform bool hasTex;

void main()
{
	if (hasTex)
		color = texture(mainTex, TexCoord) * Color;
	else
		color = Color;
}