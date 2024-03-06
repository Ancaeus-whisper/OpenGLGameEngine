#include "TestTexture2D.h"

namespace test
{
    TestTexture2D::TestTexture2D():m_Proj(glm::ortho(0.0,8.0,0.0,6.0)),m_View(glm::translate(glm::mat4(1.0f),glm::vec3(4,3,0))),transformA(0,0,0)
    {
        //图元数据
        float position[]=
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
        //OpenGL对象初始化
        m_VAO                       =std::make_unique<VertexArray>();
        m_VBO                       =std::make_unique<VertexBuffer>(position,4*4*sizeof(float));
        m_IBO                       =std::make_unique<IndexBuffer>(indices,6);
        VertexBufferLayout* Layout  =new VertexBufferLayout;
        m_Shader                    =std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");

        Layout->Push<float>(2);
        Layout->Push<float>(2);

        m_VAO->AddBuffer(*m_VBO,*Layout);
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_color",1,1,1,1);
        m_Texture=std::make_unique<Texture>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default_tex.jpg");
        m_Texture->Bind(0);
        m_Shader->SetUniform1i("u_Texture",0);
        
        m_VAO->UnBind();
        m_VBO->UnBind();
        m_IBO->UnBind();
        m_Shader->UnBind();
    }
    TestTexture2D::~TestTexture2D()
    {
    }
    void TestTexture2D::OnUpdate(float deltaTime)
    {
    }
    void TestTexture2D::OnRender()
    {
        GLCALL(glClearColor(0.5f,0.5f,0.5f,1.0f));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));

        Renderer RendererPipeline;

        m_Texture->Bind(0);
        m_VAO->Bind();
        {
            glm::mat4 Model(glm::translate(glm::mat4(1.0),transformA));
            glm::mat4 MVP=m_Proj*m_View*Model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP",MVP);
            RendererPipeline.Draw(*m_VAO,*m_IBO,*m_Shader);
        }
        m_VAO->UnBind();
    }
    void TestTexture2D::OnImguiRender()
    {
        ImGui::SliderFloat2("Transform:",&transformA.x,-8.0,8.0);
        ImGui::Text("Application Average %.3f FrameRate(%.f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
    }
}