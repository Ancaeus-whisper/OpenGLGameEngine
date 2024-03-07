#pragma once
#include <memory>

#include "Test.h"

#include "../DependencyManager.h"
#include "../Renderer.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"

#include "../Object/Camera.h"

//TODO 生成框架测试摄像机

namespace test
{
    class TestCameraScene:public Test
    {
        private:
            std::unique_ptr<OWL::Camera> m_MainCamera;

            std::unique_ptr<VertexArray>   m_VAO;
            std::unique_ptr<VertexBuffer>  m_VBO;
            std::unique_ptr<IndexBuffer>   m_IBO;
            std::unique_ptr<Shader>        m_Shader;
            std::unique_ptr<Texture>       m_Texture;

            glm::mat4                      m_Proj;
            glm::mat4                      m_View;

        public:
            TestCameraScene();
            ~TestCameraScene();

            void OnRender();
            void OnUpdate(float deltaTime);
            void OnImguiRender();
    };
}
