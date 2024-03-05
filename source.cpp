#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <memory>

#pragma region 2D渲染测试
//float vertices[]=
//                {
//                    0.5f, 0.5f, 1.0f, 1.0f,   // 右上角
//                    0.5f,-0.5f, 1.0f, 0.0f,  // 右下角
//                   -0.5f,-0.5f, 0.0f, 0.0f,// 左下角
//                   -0.5f, 0.5f, 0.0f, 1.0f 
//                };
//
//unsigned int indices[] = {
//    0, 1, 3,
//    1, 2, 3  
//};
#pragma endregion

#pragma region 3D渲染测试
const float position[] =
        {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        unsigned int indices[] =
        {
            0,1,2,3,4,5,
            6,7,8,9,10,11,
            12,13,14,15,16,17,
            18,19,20,21,22,23,
            24,25,26,27,28,29,
            30,31,32,33,34,35
        };

         glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

#pragma endregion

glm::mat4 View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.0)));

glm::mat4 Proj(glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f));

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
    

    #pragma region 2D渲染测试
    //std::unique_ptr<VertexArray> VAO=std::make_unique<VertexArray>();
    //std::unique_ptr<VertexBuffer> VBO=std::make_unique<VertexBuffer>((void*)vertices,4*4*sizeof(float));
    //std::unique_ptr<VertexBufferLayout> Layout=std::make_unique<VertexBufferLayout>();
    //std::unique_ptr<IndexBuffer> IBO=std::make_unique<IndexBuffer>(indices,6);
    //std::unique_ptr<Shader> shader=std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");
    //std::unique_ptr<Texture> texture=std::make_unique<Texture>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default_tex.jpg");
    //
    //
    //Layout->Push<float>(2);//坐标
    //Layout->Push<float>(2);//纹理坐标
    //
    //VAO->AddBuffer(*VBO,*Layout);
    //shader->Bind();
    //shader->SetUniform4f("u_color",1,1,1,0);
    //GLCALL(texture->Bind(0));
    //shader->SetUniform1i("u_Texture",0);
    //
    //VAO->UnBind();
    //VBO->UnBind();
    //IBO->UnBind();
    //shader->UnBind();
    #pragma endregion

    #pragma region 3D渲染测试
    GLCALL(glEnable(GL_BLEND));
    GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::unique_ptr<VertexArray> VAO=std::make_unique<VertexArray>();
    std::unique_ptr<VertexBuffer> VBO=std::make_unique<VertexBuffer>((void*)position,5*6*6*sizeof(float));
    std::unique_ptr<VertexBufferLayout> Layout=std::make_unique<VertexBufferLayout>();
    std::unique_ptr<IndexBuffer> IBO=std::make_unique<IndexBuffer>(indices,6*6);
    std::unique_ptr<Shader> shader=std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");
    std::unique_ptr<Texture> texture=std::make_unique<Texture>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default_tex.jpg");

    Layout->Push<float>(3);
    Layout->Push<float>(2);

    VAO->AddBuffer(*VBO,*Layout);
    shader->Bind();
    shader->SetUniform4f("u_color",1,1,1,1);
    texture->Bind(0);
    shader->SetUniform1i("u_Texture",0);

    VAO->UnBind();
    VBO->UnBind();
    IBO->UnBind();
    shader->UnBind();
    #pragma endregion

    //主循环
    while(!glfwWindowShouldClose(window))
    {    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        GLCALL(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));

        #pragma region 2D渲染测试
        //shader->Bind();
        //glm::mat4 MVP=Proj*View*Model;
        //shader->SetUniformMat4f("u_MVP",MVP);
        //VAO->Bind();
        //IBO->Bind();
        //GLCALL(glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
        #pragma endregion
        
        #pragma region 3D渲染测试
        glm::mat4 Model(1.0f);
        for(int i=0;i<10;i++)
        {
            Model=glm::translate(Model,cubePositions[i]);
            float angle = 20.0f * i; 
            Model = glm::rotate(Model, glm::radians(angle), glm::vec3(0.1f, 0.03f, 0.05f));
            glm::mat4 MVP = Proj * View * Model;
            shader->Bind();
            shader->SetUniformMat4f("u_MVP",MVP);
            VAO->Bind();
            IBO->Bind();
            GLCALL(glDrawElements(GL_TRIANGLES, IBO->GetCount(), GL_UNSIGNED_INT, nullptr));
        }
        
        #pragma endregion
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