#include "DependencyManager.h"
#include "Test/Test.h"
#include "Test/TestClearColor.h"
#include "Test/TestTexture2D.h"
#include "Test/TestTexture3D.h"
#include "Test/TestCameraScene.h"
#include "Test/TestFPSCameraScene.h"

#include "Singleton/InputManager.h"
#include "Singleton/WindowManager.h"
#include "Singleton/TimeManager.h"
int main(void)
{
    OWL::global::InputManager *inputManager=OWL::global::InputManager::getInstance();
    OWL::global::WindowManager* window=OWL::global::WindowManager::getInstance();
    OWL::global::TimeManager* timer=OWL::global::TimeManager::getInstance();

    window->resize(800,600);
    window->SetTitle("MyGameEngine");
    window->SetDebug(true);
    //window->SetCallback(OWL::global::WindowManager::CallbackType::frameBuffer,[](GLFWwindow* window, int width, int height){glViewport(0, 0, width, height);});

    window->EnableImgui();

    Renderer RendererPipeline;

 
    #pragma region 测试框架搭建
    test::Test* current=nullptr;
    test::TestMenu* testMenu=new test::TestMenu(current);
    current=testMenu;

    testMenu->RegisterTest<test::TestClearColor>("ClearColor");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");
    testMenu->RegisterTest<test::TestTexture3D>("Texture3D");
    testMenu->RegisterTest<test::TestCameraScene>("CameraScene");
    testMenu->RegisterTest<test::TestFPSCameraScene>("FPSCameraScene");
    #pragma endregion



    //主循环
    while(!window->ShouldClose())
    { 
        timer->Update();
        RendererPipeline.Clear();

        GLCALL(glClearColor(0.0f,0.0f,0.0f,1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        window->ImGuiRender(current,testMenu);

        window->EndFrame( );
    }

    return 0;
}