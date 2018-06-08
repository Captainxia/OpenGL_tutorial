#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<stdio.h>
#include"Shader.h"
#include<SOIL/SOIL.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//#include<iostream.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action,
       int mode);
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f
};
glm::vec3 cubePositions[] = {
          glm::vec3( 0.0f, 0.0f, 0.0f),
          glm::vec3( 2.0f, 5.0f, -15.0f),
          glm::vec3(-1.5f, -2.2f, -2.5f),
          glm::vec3(-3.8f, -2.0f, -12.3f),
          glm::vec3( 2.4f, -0.4f, -3.5f),
          glm::vec3(-1.7f, 3.0f, -7.5f),
          glm::vec3( 1.3f, -2.0f, -2.5f),
          glm::vec3( 1.5f, 2.0f, -2.5f),
          glm::vec3( 1.5f, 0.2f, -1.5f),
          glm::vec3(-1.3f, 1.0f, -1.5f)
};

float PI = 3.14159;
GLuint indices[] = {
    0,1,3,
    1,2,3
};
const int WIDTH = 800;
const int HEIGHT = 600;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"texture",nullptr,nullptr);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    if(glewInit()!= GLEW_OK)
    {
        fprintf(stderr,"error: glew init failed!");
        return -1;
    }

    GLuint vao, vbo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1, &vbo);
   // glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5* sizeof(GL_FLOAT), (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    int width=0;
    int height = 0;
    unsigned char* image = SOIL_load_image("container.jpg",&width,&height,0,SOIL_LOAD_RGB);
    


    GLuint texture1;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D,0);

    GLuint texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    image = SOIL_load_image("awesomeface.png",&width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    cout<< "texture images read"<<endl;
    
    //glm::vec3 cameraPos = glm::vec3(0.0f,0.0f, 3.0);
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    //glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    //glm::vec3 cameraRight = glm::normalize(glm::cross(up,cameraDirection));
    //glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    // glm::mat4 view;
    // view = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f),
    //                 glm::vec3(0.0f,0.0f,0.0f),
    //                 glm::vec3(0.0f,1.0f,0.0f));
    


    Shader my_shader("cubic.vs", "cubic.frag");
    cout<< "shader files loaded"<<endl;
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f,0.7f,0.8f,1.0f);
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSetKeyCallback(window,key_callback);
        my_shader.Use();
        glm::mat4 model;
        model = glm::rotate(model,0.0f, glm::vec3(1.0f,0.3f,0.5f));
        //std::cout<<model<<endl;(-55.0f/360.0f)
        //GLfloat radius = 10.0f;
        //GLfloat camx = sin(glfwGetTime()) * radius;
        //GLfloat camz = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // view = glm::lookAt(glm::vec3(camx,0.0f, camz),
        //                     glm::vec3(0.0f,0.0f,0.0f),
        //                     glm::vec3(0.0f,1.0f,0.0f));
        // view = glm::lookAt(glm::vec3(0.0f,0.0f,3.0f),
        //             glm::vec3(0.0f,0.0f,0.0f),
        //             glm::vec3(0.0f,1.0f,0.0f));
        //view = glm::translate(view, glm::vec3(0.0f,0.0f,-5.0f));
        glm::mat4 projection;
        projection = glm::perspective(45.0f, (800.0f/600.0f), 0.1f, 100.0f);
        
        //trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));
        //trans= glm::rotate_slow(trans, PI/2.0f,glm::vec3(0.0,0.0,1.0));
        //trans = glm::rotate(trans, (GLfloat)glfwGetTime()* 0.5f,glm::vec3(0.0f,0.0f,1.0f));
        //trans= glm::scale(trans,glm::vec3(0.5,0.5,0.5));
        GLuint modelLoc = glGetUniformLocation(my_shader.Program,"model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        GLuint viewLoc = glGetUniformLocation(my_shader.Program,"view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        GLuint projectionLoc = glGetUniformLocation(my_shader.Program, "projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE, glm::value_ptr(projection));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(my_shader.Program,"ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(my_shader.Program,"ourTexture2"), 1);

        //glBindTexture(GL_TEXTURE_2D, texture);
        //shader.Use();
        glBindVertexArray(vao);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        
        for(GLuint i =0; i< 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = glfwGetTime()* 40.0f / 180.0f * PI * i;
            model = glm::rotate(model, angle, glm::vec3(0.5f, 1.5f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
   //glDeleteBuffers(1, &ebo);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

 void key_callback(GLFWwindow* window, int key, int scancode, int action,
       int mode)
{
    //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    GLfloat cameraSpeed = 0.05f;
    if(key == GLFW_KEY_W)
        cameraPos += cameraSpeed * cameraFront;
    if(key == GLFW_KEY_S)
        cameraPos -= cameraSpeed * cameraFront;
    if(key == GLFW_KEY_A)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) *
    cameraSpeed;
    if(key == GLFW_KEY_D)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) *
    cameraSpeed;
   }