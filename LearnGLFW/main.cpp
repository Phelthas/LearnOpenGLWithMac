//
//  main.cpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/8.
//


#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glext.h>
#include <math.h>
#include <iostream>


#if !defined(_STRINGIFY)
#define __STRINGIFY( _x )   # _x
#define _STRINGIFY( _x )   __STRINGIFY( _x )
#endif

static const char * kPassThruVertex = _STRINGIFY(

attribute vec4 position;
attribute mediump vec4 texturecoordinate;
varying mediump vec2 coordinate;

void main()
{
    gl_Position = position;
    coordinate = texturecoordinate.xy;
}
                                                 
);

static const char * kPassThruFragment = _STRINGIFY(
                                                   
varying highp vec2 coordinate;
uniform sampler2D videoframe;

void main()
{
    gl_FragColor = texture2D(videoframe, coordinate);
}
                                                   
);

GLuint compileShaders0(void);

struct vector3 {
    float position[3];
};

int main0(int argc, const char * argv[]) {
    
    
    GLFWwindow* win;
    if(!glfwInit()){
        return -1;
    }
    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
    if(!win)
    {
        glfwTerminate();
        return -1;
    }
        
//    const GLubyte *version = glGetString(GL_VERSION);
//
//    GLuint program = compileShaders0();
//
//    glUseProgram(program);
    
//    vector3 vertices[] = {
//        {-0.5, 0.0, 0.0,},
//        {0.5, 0.5, 0.0,},
//        {0.5, -0.5, 0.0,},
//    };
    
    vector3 vertices[] = {
        -0.5, 0.0, 0.0,
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
    };
    
    
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    glfwMakeContextCurrent(win);
    
    GLuint program = compileShaders0();

    glUseProgram(program);
    
    
    while(!glfwWindowShouldClose(win)){
//        double time = glfwGetTime();
        
//        glClearColor(sin(time) + 0.5, cos(time) + 0.5, 0.0f, 1.0f);
        
        glClearColor(0.25, 0.25, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glPointSize(40);
        
        
        
        glEnableVertexAttribArray(0);//这一句很关键
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    
        glDrawArrays(GL_POINTS, 0, 1);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

GLuint compileShaders0(void) {
    GLuint vertexShader = -1;
    GLuint fragmentShader = -1;
    GLuint program = -1;

//#version 450 core \

    static const GLchar *vertexShaderSource[] = {
        "void main(void)    \n"
        "{ \n"
        "gl_Position = vec4(0.5, 0.5, 0.0, 1.0); \n"
        "} \n"
    };
    

    static const GLchar *fragmentShaderSource = " \
    void main(void) \
    { \
    gl_FragColor = vec4(0.0, 0.8, 1.0, 1.0); \
    } \
    ";
    
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint status = -1;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(vertexShader, logLength, &logLength, log);
            std::cout << "ERROR\n" << log << std::endl;
            free(log);
        }
    }
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    status = -1;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetShaderInfoLog(fragmentShader, logLength, &logLength, log);
            std::cout << "ERROR\n" << log << std::endl;
            free(log);
        }
    }
    
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    status = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetProgramInfoLog(program, logLength, &logLength, log);
            std::cout << "ERROR\n" << log << std::endl;
            free(log);
        }
        return false;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

