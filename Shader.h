#include "DependencyManager.h"

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

        void Bind()const;
        void UnBind()const;

        unsigned int CompileShader(unsigned int type,const std::string& source)const;
        int CreateShader(const std::string& vertexShader,const std::string& fragmentShader)const;

        ShaderSource ShaderParse(const std::string& filePath);

        #pragma region 设置uniform
        void SetUniform1i(const std::string name,int value);
        void SetUniform1f(const std::string name,float value);
        void SetUniform2f(const std::string name,float v1,float v2);
        void SetUniform3f(const std::string name,float v1,float v2,float v3);
        void SetUniform4f(const std::string name,float v1,float v2,float v3,float v4);

        void SetUniformMat3f(const std::string& name,const glm::mat3& matrix);
        void SetUniformMat4f(const std::string& name,const glm::mat4& matrix);
        #pragma endregion

        int GetUniformLocation(const std::string& name);
};