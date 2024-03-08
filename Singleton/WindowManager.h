#ifndef _WINDOW_
#define _WINDOW_

#include "Singleton.h"
#include "TimeManager.h"
#include "../Test/Test.h"
#include "../DependencyManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <functional>

namespace OWL
{
    namespace global
    {
        class WindowManager:public Singleton<WindowManager>
        {
            public:
                WindowManager();
                ~WindowManager();

                enum CallbackType{frameBuffer,cursorpos,scroll};    
                using GLFWframebuffersizefun = std::function<void(GLFWwindow*, int, int)>;
                using GLFWcursorposfun = std::function<void(GLFWwindow*, double, double)>;
                using GLFWscrollfun = std::function<void(GLFWwindow*, double, double)>;            
                void SetCallback(CallbackType type,GLFWframebuffersizefun callback);//设置回调函数

                GLFWwindow* GetWindow()const{return m_Window;}
                //glfw函数
                void resize(int width,int height);
                void SetTitle(const std::string& title);

                inline int GetWidth()const{return m_Width;}
                inline int GetHeight()const{return m_Height;}

                void EndFrame();

                int ShouldClose();
                inline void Quit(){glfwSetWindowShouldClose(m_Window, true);}

                //imgui函数
                void EnableImgui();
                void SetDebug(bool value);
                void ImguiNewFrame();

                void ImGuiRender(test::Test* &current,test::TestMenu* testMenu);


            private:
                //glfw窗口类
                GLFWwindow* m_Window;
                std::string m_Title;
                int m_Width;
                int m_Height;
                bool isDebug;

                //调试窗口
                //ImGuiIO& m_ImGui_IO;
                bool isImGuiActive;

        };

    }
}
#endif