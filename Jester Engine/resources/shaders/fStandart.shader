#version 330

in vec4 Color;
in vec2 TexCoord;
in float texIndex;

out vec4 color;

uniform sampler2D[32] mainTex;

void main()
{
	//int index = int(texIndex);
	//color = texture(mainTex[index], TexCoord) * Color;
	color = vec4(1, 1, 1, 1);
}