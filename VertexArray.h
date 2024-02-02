#pragma once
#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
    private:
        unsigned int m_RendererID;

    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& VBO,const VertexBufferLayout& Layout);

        void Bind();
        void UnBind();
};