//
//  lesson1.cpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/9.
//

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>


#if !defined(_STRINGIFY)
#define __STRINGIFY( _x )   # _x
#define _STRINGIFY( _x )   __STRINGIFY( _x )
#endif

GLuint compileShaders(void);

struct vector3 {
    float position[3];
};

int main(int argc, const char * argv[]) {
    
    
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
        -0.5, 0.0, 0.0,
        0.5, 0.5, 0.0,
        0.5, -0.5, 0.0,
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);//这一句很关键
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    
    GLuint program = compileShaders();
    
    while(!glfwWindowShouldClose(win)){
//        double time = glfwGetTime();
        
        glClearColor(0.25, 0.25, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glUseProgram(program);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

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
