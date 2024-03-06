#include "Renderer.h"


void Renderer::Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader)const
{
    shader.Bind();
    VAO.Bind();
    IBO.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES,IBO.GetCount(),GL_UNSIGNED_INT,nullptr));
}

void Renderer::Clear()const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}
