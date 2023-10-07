#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec4 color;
uniform mat4 modelMatrix;
out vec4 fragColor;
void main () {
    gl_Position = modelMatrix * vec4 (vp, 1.0);
	fragColor = color;
}