#pragma once
#include "DependencyManager.h"

class IndexBuffer
{
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;

    public:
        IndexBuffer(const unsigned int* indice,unsigned int count);
        ~IndexBuffer();

        void Bind()const;
        void UnBind()const;

        inline unsigned int GetCount()const{return m_Count;}
};