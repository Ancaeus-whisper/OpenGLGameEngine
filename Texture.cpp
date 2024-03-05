#include "Texture.h"
#include <stb_image/stb_image.h>

Texture::Texture(const std::string& path)
:m_RendererID(0),m_Filepath(path),m_localBuffer(nullptr),
 m_Width(0),m_Height(0),m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    
    m_localBuffer=stbi_load(m_Filepath.c_str(),&m_Width,&m_Height,&m_BPP,4);//rgba
    if(!m_localBuffer){
    std::cout << "Failed to load texture" << std::endl;
    }

    GLCALL(glGenTextures(1,&m_RendererID));
    GLCALL(glBindTexture(GL_TEXTURE_2D,m_RendererID));

    GLCALL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR));
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    GLCALL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_Width,m_Height,0,
                 GL_RGBA,GL_UNSIGNED_BYTE,m_localBuffer));
    
    glBindTexture(GL_TEXTURE_2D,0);

}

Texture::~Texture()
{
    glDeleteTextures(1,&m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
    GLCALL(glActiveTexture(GL_TEXTURE0+slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D,m_RendererID));
}

void Texture::UnBind() const
{
    GLCALL(glBindTexture(GL_TEXTURE_2D,0));
}
