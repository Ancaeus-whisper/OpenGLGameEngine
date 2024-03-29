#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *indice, unsigned int count):m_Count(count)
{
    glGenBuffers(1,&m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),indice,GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_RendererID);
}

void IndexBuffer::Bind()const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
}

void IndexBuffer::UnBind()const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}
