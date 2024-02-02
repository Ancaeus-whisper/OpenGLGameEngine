#include <glad/glad.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

struct ShaderSource
{
    std::string vertexShader;
    std::string fragmentShader;
};

class Shader
{
    private:
        std::string m_Filepath;
        unsigned int m_RendererID;
        std::unordered_map<std::string,int> m_Locations;

    public:
        Shader(std::string filePath);
        ~Shader();

        void Bind();
        void UnBind();

        unsigned int CompileShader(unsigned int type,const std::string& source)const;
        int CreateShader(const std::string& vertexShader,const std::string& fragmentShader)const;

        ShaderSource ShaderParse(const std::string& filePath);

};