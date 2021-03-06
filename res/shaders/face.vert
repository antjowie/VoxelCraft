#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in float aTexIndex;

out vec3 normal;
out vec2 uv;
out flat float texIndex; 

out vec3 vertPos;
out float skyIntensity;
out float skyDiffuseIntensity;
out vec3 skyLightDir;
out vec3 skyLightColor;

uniform mat4 aVP;
uniform mat4 aModel;

uniform float aSkyIntensity;
uniform float aSkyDiffuseIntensity;
uniform vec3 aSkyLightDir;
uniform vec3 aSkyLightColor;

void main()
{
    normal = aNormal;
    uv = aUV;
    texIndex = aTexIndex;
 
    vertPos = aPos;
    skyIntensity = aSkyIntensity;
    skyDiffuseIntensity = aSkyDiffuseIntensity;
    skyLightDir = aSkyLightDir;
    skyLightColor = aSkyLightColor;

    gl_Position = aVP * aModel * vec4(aPos ,1.0f);
    
    //gl_Position = vec4(aPos.xy,-1.0f ,1.0f);
}