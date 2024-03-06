#ifndef _ENGINE_LIBRARY_
    #define _ENGINE_LIBRARY_
    #include <glad/glad.h>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <stb_image/stb_image.h>

    #define ASSERT(x) if(!x) __debugbreak();
    #define GLCALL(x) GLClearError();\
            x;\
            ASSERT(GLLogCall(#x,__FILE__,__LINE__))

    void GLClearError();

    bool GLLogCall(const char* function, const char* file, int line);
#endif