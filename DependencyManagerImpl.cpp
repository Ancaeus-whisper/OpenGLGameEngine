#include "DependencyManager.h"
#include <iostream>
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error](" << error << "):" << function << std::endl
            << file << ":" << "第" << line << "行" << std::endl;
        return false;
    }
    return true;
}
