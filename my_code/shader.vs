#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
uniform  vec3 offset;
out vec3 ourColor;
out vec3 vertexpos;
void main()
{
    gl_Position = vec4(position.x + offset.x,-position.y,position.z, 1.0f);
    ourColor = color;
    vertexpos = position;
}