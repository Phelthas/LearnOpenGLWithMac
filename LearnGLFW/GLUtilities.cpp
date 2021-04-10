//
//  GLUtilities.cpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/10.
//

#include "GLUtilities.hpp"
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <iostream>
#include "GLUtilities.hpp"


GLuint compileShaders(void) {
    GLuint vertexShader = -1;
    GLuint fragmentShader = -1;
    GLuint program = -1;

//#version 450 core \

    static const GLchar *vertexShaderSource[] = {
        "#version 330 core \n"
        "layout (location = 0) in vec3 Position; \n"
        "void main(void)    \n"
        "{ \n"
        "gl_Position = vec4(Position.x, Position.y, Position.z, 1.0); \n"
        "} \n"
    };
    

    static const GLchar *fragmentShaderSource = " \
    #version 330 core \
    out vec4 FragColor; \
    void main(void) \
    { \
    FragColor = vec4(0.0, 0.8, 1.0, 1.0); \
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
