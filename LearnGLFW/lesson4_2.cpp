//
//  lesson4_2.cpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/18.
//

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include "GLUtilities.hpp"


#if !defined(_STRINGIFY)
#define __STRINGIFY( _x )   # _x
#define _STRINGIFY( _x )   __STRINGIFY( _x )
#endif


int main4_2(int argc, const char * argv[]) {
    
    
    GLFWwindow* win;
    if(!glfwInit()){
        return -1;
    }
    
    /**
     The Core Profile does not support the old fixed pipeline anymore, and requires you to implement your own shaders in GLSL.
     You need to use Vertex Array Objects (VAO). Look up glGenVertexArrays and glBindVertexArray.
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
    if(!win)
    {
        glfwTerminate();
        return -1;
    }
    
    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f,   // top left
        0.0, 0.0, 0.0,
    };
    
    GLuint indices[] = {
        0, 1, 4,  // first Triangle
    };

    GLuint indices2[] = {
        4, 2, 3   // second Triangle
    };

    glfwMakeContextCurrent(win);
    
    const GLubyte *version = glGetString(GL_VERSION);
    std::cout << "opengl version: " << version << std::endl;
    
    
    
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //stride参数 也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);//这一句很关键
    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);//如果不写这一句，可以让两个ebo公用同一个vbo

    glBindVertexArray(0);
    
    
    GLuint vertexArrayObject2;
    glGenVertexArrays(1, &vertexArrayObject2);
    glBindVertexArray(vertexArrayObject2);
    
    GLuint elementBufferObject2;
    glGenBuffers(1, &elementBufferObject2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    
    //stride参数 也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);//这一句很关键
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    
    GLuint program = compileShaders();
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while(!glfwWindowShouldClose(win)){
//        double time = glfwGetTime();
        
        glClearColor(0.25, 0.25, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glUseProgram(program);
        glBindVertexArray(vertexArrayObject);//注意这里绑定的还是VAO，EBO是一致绑定着的，没解绑过
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glBindVertexArray(vertexArrayObject2);//注意这里绑定的还是VAO，EBO是一致绑定着的，没解绑过
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}




