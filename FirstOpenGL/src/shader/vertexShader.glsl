#version 440 core
layout (location = 0) in vec3 aPos;

uniform float t;
out vec4 vertexColor;

void main()
{
    mat2 rotate;
    rotate[0]=vec2(cos(t),-sin(t));
    rotate[1]=vec2(sin(t),cos(t));
    mat2 point;
    point[0]=vec2(aPos.x,-aPos.y);
    point[1]=aPos.yx;
    mat2 result = matrixCompMult(point,rotate);
    gl_Position = vec4(aPos.xyz, 1.0);
    vertexColor = vec4(result[0].x/2+0.5,-result[0].y/2+0.5,0.5,1.0);
}
