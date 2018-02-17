#version 440 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D myTexure;
uniform sampler2D texWall;

void main()
{
    FragColor = mix(texture(myTexure,texCoord),texture(texWall,texCoord),.5);
}