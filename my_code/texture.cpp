#include<stdio.h>
#include<GL/glew.h>
#include<SOIL/SOIL.h>
#include<GLFW/glfw3.h>
#include"Shader.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
GLfloat vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f,0.0f,0.0f,1.0f,1.0f,
    0.5f,-0.5f, 0.0f, 0.0f,1.0f,0.0f,1.0f,0.0f,
   -0.5f,-0.5f, 0.0f, 0.0f,0.0f,1.0f,0.0f,0.0f,
   -0.5f, 0.5f, 0.0f, 1.0f,1.0f,0.0f,0.0f,1.0f
};

float PI = 3.14159;
GLuint indices[] = {
    0,1,3,
    1,2,3
};
const int WIDTH = 800;
const int HEIGHT = 600;

const GLchar* vertexShaderSource = "#version 410 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec2 texCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"gl_Position = projection * view * model * vec4(position, 1.0f);\n"
"ourColor = color;\n"
"TexCoord = vec2(texCoord.x, 1.0f -texCoord.y);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 410 core\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"out vec4 color;\n"
"uniform sampler2D ourTexture1;\n"
"uniform sampler2D ourTexture2;\n"
"void main()\n"
"{\n"
"color = mix(texture(ourTexture1, TexCoord),texture(ourTexture2, TexCoord), 0.2);\n"
"}\0";

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "error: glfw init failed!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"texture",nullptr,nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if(glewInit()!= GLEW_OK)
    {
        fprintf(stderr,"error: glew init failed!");
        return -1;
    }

    int width=0;
    int height = 0;
    unsigned char* image = SOIL_load_image("container.jpg",&width,&height,0,SOIL_LOAD_RGB);
    //cout<< "img1 read success!"<< endl;
    GLuint texture;
    glGenTextures(1, &texture);
    cout<< "img1 read success!"<< endl;
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    cout<< "img1 read success!"<< endl;
    printf("image1 height %d, image width %d", height, width );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
    //    GL_UNSIGNED_BYTE, image);
    cout<< "img1 read success!"<< endl;
    printf("image height %d, image width %d", height, width );
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D,0);
    cout<< "SOIL_free_image_data success!"<< endl;
    GLuint texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    width = 1;
    cout<< "img2 reading "<< endl;
    image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
 
    //image = SOIL_load_image("awesomeface.png", &width, &height, 0,SOIL_LOAD_RGB);
    cout<< "img2 read success!"<< endl;
    
    printf("width %d",width);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLint success;
    //GLchar infoLog[512];
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        fprintf(stderr,"error: vertex shader compilation failed!\n");
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        fprintf(stderr, "error: fragment shader compilation failed!\n");
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success)
    {
        fprintf(stderr, "error: shader program link failed!\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //Shader shader("tex.vs","tex.fg");
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8* sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8* sizeof(GL_FLOAT), (GLvoid*)(6* sizeof (GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glm::mat4 model;
        model = glm::rotate(model,0.0f, glm::vec3(0.5f,1.0f,0.0f));
        //std::cout<<model<<endl;(-55.0f/360.0f)
        glm::mat4 view;
        view = glm::translate(view, glm::vec3(0.0f,0.0f,-1.5f));
        glm::mat4 projection;
        projection = glm::perspective((100.0f/360.0f)*PI, (800.0f/600.0f), 0.0f, 100.0f);

        //trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));
        //trans= glm::rotate_slow(trans, PI/2.0f,glm::vec3(0.0,0.0,1.0));
        //trans = glm::rotate(trans, (GLfloat)glfwGetTime()* 0.5f,glm::vec3(0.0f,0.0f,1.0f));
        //trans= glm::scale(trans,glm::vec3(0.5,0.5,0.5));
        GLuint modelLoc = glGetUniformLocation(shaderProgram,"model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        GLuint viewLoc = glGetUniformLocation(shaderProgram,"view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE, glm::value_ptr(projection));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shaderProgram,"ourTexture1"), 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shaderProgram,"ourTexture2"), 1);

        //glBindTexture(GL_TEXTURE_2D, texture);
        //shader.Use();
        
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}
