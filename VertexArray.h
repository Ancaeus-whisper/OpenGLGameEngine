#pragma once
#include "DependencyManager.h"
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

        void Bind()const;
        void UnBind()const;
};