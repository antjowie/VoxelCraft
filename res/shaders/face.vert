#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in int aTexIndex;

out vec2 uv;
out flat int texIndex; 

uniform mat4 aVP;

void main()
{
    uv = aUV;
    texIndex = aTexIndex;
    gl_Position = aVP * vec4(aPos ,1.0f);
    gl_Position = vec4(aPos ,1.0f);
}