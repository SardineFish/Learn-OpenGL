#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float t;
uniform mat4 transform;
out vec4 vertexColor;
out vec2 texCoord;

void main()
{
    mat2 rotate;
    rotate[0]=vec2(cos(t),-sin(t));
    rotate[1]=vec2(sin(t),cos(t));
    mat2 point;
    point[0]=vec2(aPos.x,-aPos.y);
    point[1]=aPos.yx;
    mat2 result = matrixCompMult(point,rotate);
    gl_Position = transform * vec4(aPos, 1.0f);
    vertexColor = vec4(result[0].x/2+0.5,-result[0].y/2+0.5,0.5,1.0);
    texCoord = aTexCoord;
}
