//
//  GLUtilities.hpp
//  LearnGLFW
//
//  Created by billthaslu on 2021/4/10.
//

#ifndef GLUtilities_hpp
#define GLUtilities_hpp

#include <OpenGL/gltypes.h>

GLuint compileShaders(void);

GLuint compileShadersWithSources(const GLchar *vertexShaderSource, const GLchar *fragmentShaderSource);

#endif /* GLUtilities_hpp */
