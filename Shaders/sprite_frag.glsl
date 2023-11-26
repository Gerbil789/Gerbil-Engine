#version 330 core

in vec2 TexCoords;
out vec4 outColor;

uniform sampler2D textureUnitID;
uniform vec3 color;

void main()
{
    vec4 texColor = texture(textureUnitID, TexCoords);

    if (texColor.a == 0.0) {
        discard; // Discard the fragment (make it transparent)
    } else {
        outColor = vec4(texColor.rgb * texColor.a, texColor.a);
    }

    outColor.rgb *= color;
    outColor.a = texColor.a;
}