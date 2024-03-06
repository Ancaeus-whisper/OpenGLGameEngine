#include "TestTexture3D.h"

namespace test
{
    TestTexture3D::TestTexture3D():m_Proj(glm::perspective(glm::radians(45.0f),8/(float)6,0.1f,100.0f)),
                                   m_View(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-0.3f))),transformA(0.0f,0.0f,0.0f),transformB(2.0f,5.0f,-15.0f)
    {
        #pragma region 图元数据
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
        
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glEnable(GL_DEPTH_TEST));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VAO                           =std::make_unique<VertexArray>();
        m_VBO                           =std::make_unique<VertexBuffer>((void*)position,5*6*6*sizeof(float));
        VertexBufferLayout* Layout      =new VertexBufferLayout;
        m_IBO                           =std::make_unique<IndexBuffer>(indices,6*6);
        m_Shader                        =std::make_unique<Shader>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default.shader");
        m_Texture                       =std::make_unique<Texture>("F:\\CodeRepository\\ComputerGraph\\OpenGLGameEngine\\Resource\\default_tex.jpg");

        Layout->Push<float>(3);
        Layout->Push<float>(2);
//  
        m_VAO->AddBuffer(*m_VBO,*Layout);
        m_Shader->Bind();
        m_Shader->SetUniform4f("u_color",1,1,1,1);
        m_Texture->Bind(0);
        m_Shader->SetUniform1i("u_Texture",0);
        
        m_VAO->UnBind();
        m_VBO->UnBind();
        m_IBO->UnBind();
        m_Shader->UnBind();
    }
    TestTexture3D::~TestTexture3D()
    {
    }
    void TestTexture3D::OnRender()
    {
        GLCALL(glClearColor(0.0f,0.0f,0.0f,1.0f));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer RendererPipeline;

        m_VAO->Bind();
        {
            glm::mat4 Model(glm::translate(glm::mat4(1.0),transformA));
            glm::mat4 MVP=m_Proj*m_View*Model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP",MVP);
            RendererPipeline.Draw(*m_VAO,*m_IBO,*m_Shader);
        }
        m_VAO->Bind();
        {
            glm::mat4 Model(glm::translate(glm::mat4(1.0),transformB));
            glm::mat4 MVP=m_Proj*m_View*Model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP",MVP);
            RendererPipeline.Draw(*m_VAO,*m_IBO,*m_Shader);
        }
        m_VAO->UnBind();
    }
    void TestTexture3D::OnUpdate(float deltaTime)
    {
    }
    void TestTexture3D::OnImguiRender()
    {
        ImGui::SliderFloat3("TransformA:",&transformA.x,0.0f,8.0f);
        ImGui::SliderFloat3("TransformB:",&transformB.x,0.0f,8.0f);
        ImGui::Text("Application Average %.3f FrameRate(%.f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
    }
}