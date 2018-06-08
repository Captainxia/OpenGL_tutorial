#include "Shader.h"
#include<cmath>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
//#include<SOIL.h>
#include<stdio.h>



GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,  // Top Right
         0.5f, -0.5f, 0.0f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        -0.5f,  0.5f, 0.0f,   // Top Left 
        -0.8f, -0.5f,0.0f,
        -0.7f,0.5f,0.0f
    };
GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 2, 3,   // Second Triangle
        2, 4, 5
    };
// GLfloat vertices[] = { 
//     -0.5f,-0.5f,0.0f,
//     0.5f,-0.5f,0.0f,
//     0.0f,0.5f,0.0f
// };
GLfloat vertices2[] = {
    -0.5f,-0.5f,0.0f,
    -0.8f,-0.5f,0.0f,
    -0.7f,0.5f,0.0f
};
void key_callback(GLFWwindow* window, int key, int scancod,int action, int mode);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GL_FALSE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"hello",nullptr,nullptr);
    if(window == nullptr)
    {
        fprintf(stderr,"failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit()!= GLEW_OK)
    {
        fprintf(stderr, "failed to initialize GLEW");
        return -1;
    }

    GLuint vbo, ebo;
    GLuint vao;

    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, 9* sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
   // glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat),(GLvoid*)0);
    //glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    /*
    const GLchar* vertices_shader_source = "#version 410 core\n"
    "layout(location = 0) in vec3 position;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position, 1.0);\n"
    "vertexColor = vec4(0.5f,0.0f,0.0f, 1.0f);\n"
    "}\n\0";

    const GLchar* fragmentShaderSource = "#version 410 core\n"
    //"in vec4 vertexColor;\n"
    "out vec4 color;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "color = ourColor;\n"
    "}\n\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertices_shader_source,NULL);
    glCompileShader(vertexShader);
    int success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER:vertex compilation failed!");
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR: fragment shader compilation failed!");
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR: shader program linking failed!");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);*/

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glViewport(0,0,800, 600);
    Shader ourShader("./shader.vs", "./shader.frag");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(1.0f,0.7f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(shaderProgram);
        ourShader.Use();
        GLfloat timeValue = glfwGetTime();
        //printf("time value is %f \n", timeValue);
        GLfloat greenValue = (std::sin(timeValue) / 2) + 0.5;
        GLint vertexColorLocation = glGetUniformLocation(ourShader.Program,"ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        GLint vertexOffsetLocation = glGetUniformLocation(ourShader.Program,"offset");
        glUniform3f(vertexOffsetLocation, 0.5f,0.0f,0.0f);


        glBindVertexArray(vao);
        //glBindBuffer(GL_Vertebo);
        //glDrawArrays(GL_TRIANGLES,0,6);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSetKeyCallback(window,key_callback);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glfwTerminate();
    return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode,int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}