#pragma once
#include <glad/glad.h>

class IndexBuffer
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* indice,unsigned int count);
        ~IndexBuffer();

        void Bind();
        void UnBind();

        inline unsigned int GetCount()const{return m_Count;}
};