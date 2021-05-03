#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec4 color;
layout(location = 3) in float textureIndex;
layout(location = 4) in mat4 mvp;

out vec4 Color;
out vec2 TexCoord;
out float texIndex;

uniform mat4 view;
uniform mat4 model;
//uniform vec4 color;
uniform mat4 projection;

void main()
{
	gl_Position = model * vec4(pos, 1.0f);

	Color = color;
	TexCoord = uv;
	texIndex = textureIndex;
}