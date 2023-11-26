#version 330 core

in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D textureUnitID;
uniform vec3 color;

void main()
{
	vec4 texColor = texture(textureUnitID, TexCoords) * vec4(color, 1.0f);
	outColor = texColor;
}