#pragma once
#include "DependencyManager.h"
#include <string>
#include <iostream>

class Texture
{
    private:
        unsigned int m_RendererID;
        std::string m_Filepath;
        unsigned char* m_localBuffer;
        int m_Width,m_Height,m_BPP;

    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind(unsigned int slot) const;
        void UnBind() const;

        inline int GetWidth()const{return m_Width;}
        inline int GetHeight()const{return m_Height;}

};