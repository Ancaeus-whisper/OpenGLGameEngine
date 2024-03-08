#include "WindowManager.h"

namespace OWL
{
    namespace global
    {
        WindowManager::WindowManager():m_Window(nullptr),isDebug(false),isImGuiActive(false),m_Width(800),m_Height(600),m_Title("default")
        {
            // 初始化 GLFW
            glfwInit();
        
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
            //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
            //新建视窗
            m_Window=glfwCreateWindow(m_Width,m_Height,m_Title.c_str(),NULL,NULL);
        
            if(!m_Window)
            {
                std::cout<<"Failed to create GLFW window"<<std::endl;
                glfwTerminate();
            }
            glfwMakeContextCurrent(m_Window);
        
            //glad获取函数实现
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


            glfwSetFramebufferSizeCallback(m_Window,[](GLFWwindow* window, int width, int height){glViewport(0, 0, width, height);});            
        }
        WindowManager::~WindowManager()
        {
            if(isImGuiActive){
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            }
            //释放资源
            if (m_Window != nullptr) {
                glfwDestroyWindow(m_Window);
            }

            glfwTerminate();
        }
        //XXX 我只是想把回调函数作为函数指针传递，怎么就这么难，类型别名我日恁娘......先放着
        void WindowManager::SetCallback(CallbackType type, GLFWframebuffersizefun callback)
        {
         
        // 其他类型的回调类似
            
        }
        void WindowManager::resize(int width, int height)
        {
            m_Width=width;
            m_Height=height;
            GLCALL(glfwSetWindowSize(m_Window, m_Width, m_Height));
        }
        void WindowManager::SetTitle(const std::string &title)
        {
            m_Title=title;
            GLCALL(glfwSetWindowTitle(m_Window, m_Title.c_str()));
        }
        void WindowManager::EndFrame()
        {
            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
        int WindowManager::ShouldClose()
        {
            
            return glfwWindowShouldClose(m_Window);
        }
        void WindowManager::EnableImgui()
        {
            isImGuiActive=true;

             // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            //m_ImGui_IO = ImGui::GetIO(); 
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style/
            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(m_Window, true);      
            ImGui_ImplOpenGL3_Init("#version 330 core");
        }
        void WindowManager::SetDebug(bool value)
        {
            isDebug=value;
            if(isDebug)
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
            }
            else
            {
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
            }
        }
        void WindowManager::ImguiNewFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void WindowManager::ImGuiRender(test::Test* &current, test::TestMenu* const testMenu)
        {
            ImguiNewFrame();

            if(current)
            {
                current->OnUpdate(OWL::global::TimeManager::getInstance()->getDeltaTime());
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
        }

        

        
    }
}