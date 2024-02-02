#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1,&m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &Layout)
{
    Bind();
    vbo.Bind();

    const auto& elements=Layout.GetElements();

    unsigned int offset=0;
    int index=0;
    for(auto& element:elements)
    {
        glEnableVertexAttribArray(index); 
        glVertexAttribPointer(index,element.count,element.type,element.normalized,Layout.GetStride(),(const void*)offset);
        index++;
        offset+=element.count*VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind()
{
    glBindVertexArray(0);
}
