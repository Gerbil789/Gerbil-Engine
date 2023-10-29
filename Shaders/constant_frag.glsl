#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

out vec4 outColor;

uniform Material material;


void main()
{
	outColor = vec4(material.diffuse, 1.0);
}