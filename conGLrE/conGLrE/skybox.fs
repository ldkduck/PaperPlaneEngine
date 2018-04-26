#version 330

in vec3 TexCoord0;

out vec4 FragColor;

uniform samplerCube gCubemapTexture;

void main()
{
	vec3 finalCoord = vec3(1-TexCoord0.x,1-TexCoord0.y,1-TexCoord0.z);
    FragColor = texture(gCubemapTexture, finalCoord);
}