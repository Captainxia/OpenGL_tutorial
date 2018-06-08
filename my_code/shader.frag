#version 410 core
in vec3 vertexpos;
uniform vec4 ourColor;

out vec4 color;
void main()
{
    
    color = vec4(vertexpos,1.0f);
}