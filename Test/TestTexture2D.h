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
namespace test{
    class TestTexture2D:public Test
    {
        private:
            std::unique_ptr<VertexArray>   m_VAO;
            std::unique_ptr<VertexBuffer>  m_VBO;
            std::unique_ptr<IndexBuffer>   m_IBO;
            std::unique_ptr<Shader>        m_Shader;
            std::unique_ptr<Texture>       m_Texture;

            glm::mat4                      m_Proj;
            glm::mat4                      m_View;
            glm::vec3                      transformA;

        public:
            TestTexture2D();
            ~TestTexture2D();

            void OnUpdate(float deltaTime);
            void OnRender();
            void OnImguiRender();

    };
}