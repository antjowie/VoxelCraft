#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;

uniform mat4 aMVP;

out vec4 vCol; 

void main()
{
    vCol = aCol;
    gl_Position = aMVP * vec4(aPos,1.0f);
}