#pragma once

#include "DependencyManager.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <string>
#include <iostream>

//TODO 设计渲染类
class Renderer
{
public:
         void Draw(const VertexArray& VAO,const IndexBuffer& IBO,const Shader& shader)const;
         void Clear()const; 
};