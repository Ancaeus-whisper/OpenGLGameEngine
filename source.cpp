#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <memory>

float vertices[]=
                {
                    0.5f, 0.5f, 1.0f, 1.0f,   // 右上角
                    0.5f,-0.5f, 1.0f, 0.0f,  // 右下角
                   -0.5f,-0.5f, 0.0f, 0.0f,// 左下角
                   -0.5f, 0.5f, 0.0f, 1.0f 
                };

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3  
};

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

int main(void)
{
    #pragma region 初始化
    // 设置错误回调
    glfwSetErrorCallback(errorCallback);

    // 初始化 GLFW
    if (!glfwInit()) {
        // 初始化失败的处理
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //新建视窗
    GLFWwindow* window=glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);

    if(window==NULL)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //glad获取函数实现
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }

    //注册一个回调函数动态改变视口大小
    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window,int width,int height)
                                            {
                                                glViewport(0,0,width,height);
                                            });
    #pragma endregion
    
    std::unique_ptr<VertexArray> VAO=std::make_unique<VertexArray>();
    std::unique_ptr<VertexBuffer> VBO=std::make_unique<VertexBuffer>((void*)vertices,4*4*sizeof(float));
    std::unique_ptr<VertexBufferLayout> Layout=std::make_unique<VertexBufferLayout>();
    std::unique_ptr<IndexBuffer> IBO=std::make_unique<IndexBuffer>(indices,6);
    std::unique_ptr<Shader> shader=std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");
    std::unique_ptr<Texture> texture=std::make_unique<Texture>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default_tex.jpg");
   //
//
    Layout->Push<float>(2);//坐标
    Layout->Push<float>(2);//纹理坐标
    
    VAO->AddBuffer(*VBO,*Layout);
    shader->Bind();
    shader->SetUniform4f("u_color",1,1,1,0);
    GLCALL(texture->Bind(0));
    shader->SetUniform1i("u_Texture",0);
    VAO->UnBind();
    VBO->UnBind();
    IBO->UnBind();
    shader->UnBind();
    int  success;
    char infoLog[512];

    //主循环
    while(!glfwWindowShouldClose(window))
    {    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        shader->Bind();
        VAO->Bind();
        IBO->Bind();

        GLCALL(glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
    if (window != nullptr) {
        glfwDestroyWindow(window);
    }
    
    glfwTerminate();
    return 0;
}