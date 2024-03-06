#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "DependencyManager.h"
#include "Test/Test.h"
#include "Test/TestClearColor.h"
#include "Test/TestTexture2D.h"
#include "Test/TestTexture3D.h"

#include <iostream>
#include <memory>

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
    
    Renderer RendererPipeline;

    #pragma region imgui初始化
     // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);      
    ImGui_ImplOpenGL3_Init("#version 330 core");
    #pragma endregion
 
    #pragma region 测试框架搭建
    test::Test* current=nullptr;
    test::TestMenu* testMenu=new test::TestMenu(current);
    current=testMenu;

    testMenu->RegisterTest<test::TestClearColor>("ClearColor");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
    testMenu->RegisterTest<test::TestTexture3D>("Texture3D");
    #pragma endregion



    //主循环
    while(!glfwWindowShouldClose(window))
    { 
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RendererPipeline.Clear();

        GLCALL(glClearColor(0.0f,0.0f,0.0f,1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        if(current)
        {
            current->OnUpdate(0.0f);
            current->OnRender();

            ImGui::Begin("Test");
            if(current!=testMenu&&ImGui::Button("<-"))
            {
                delete current;
                current=testMenu;
            }

            current->OnImguiRender();
            ImGui::End();
        }
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    //释放资源
    if (window != nullptr) {
        glfwDestroyWindow(window);
    }
    
    glfwTerminate();
    return 0;
}