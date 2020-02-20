#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvPos;

out vec2 TexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    TexCoord = vec2(uvPos.x, uvPos.y);
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}