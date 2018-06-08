#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
#include <GL/glew.h>

class Shader
{
    public:
        GLuint Program;
        Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcepath);
        void Use();

};
#endif