#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec2 vertexUV;
uniform mat4 modelMatrix;
out vec2 UV;


void main(){
    gl_Position =  modelMatrix * vec4(vp,1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}