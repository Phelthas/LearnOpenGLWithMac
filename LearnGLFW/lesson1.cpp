//
//  lesson1.cpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/9.
//

#include <GLFW/glfw3.h>

int main1(int argc, const char * argv[]) {
    
    
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
    
    glfwMakeContextCurrent(win);
    
    while(!glfwWindowShouldClose(win)){
      
        glClearColor(1.25, 0.25, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
                
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}



