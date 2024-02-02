#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <memory>

float vertices[]=
                {
                    0.5f, 0.5f, 0.0f,   // 右上角
                    0.5f, -0.5f, 0.0f,  // 右下角
                    -0.5f, -0.5f, 0.0f, // 左下角
                    -0.5f, 0.5f, 0.0f 
                };

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3  
};


int main(void)
{
    #pragma region 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    std::unique_ptr<VertexBuffer> VBO=std::make_unique<VertexBuffer>((void*)vertices,sizeof(vertices));
    std::unique_ptr<VertexBufferLayout> Layout=std::make_unique<VertexBufferLayout>();
    std::unique_ptr<IndexBuffer> IBO=std::make_unique<IndexBuffer>(indices,6);
    std::unique_ptr<Shader> shader=std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");

    Layout->Push<float>(3);
    VAO->AddBuffer(*VBO,*Layout);
    VAO->UnBind();

    int  success;
    char infoLog[512];

    //主循环
    while(!glfwWindowShouldClose(window))
    {    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram);
        VAO->Bind();
        IBO->Bind();
        shader->Bind();
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //释放资源
    glfwTerminate();
    return 0;
}