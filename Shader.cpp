#include "Shader.h"

Shader::Shader(std::string filePath)
{
    ShaderSource source=ShaderParse(filePath);
    m_RendererID=CreateShader(source.vertexShader,source.fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind()
{
    GLCALL(glUseProgram(m_RendererID));
}

void Shader::UnBind()
{
    GLCALL(glUseProgram(0));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) const
{
    unsigned int id=glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* msg=(char*)malloc(length*sizeof(char));\
        glGetShaderInfoLog(id,length, &length, msg);
        std::cout << "Failed to compile"<<((type==GL_VERTEX_SHADER)?"vertex":"fragment")<<" shader"<<id<<"!"<<std::endl;
        std::cout<<msg<<std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) const
{
    unsigned int program=glCreateProgram();

    unsigned int vertex=CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fragment=CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vertex);
    glAttachShader(program,fragment);

    glLinkProgram(program);
    glValidateProgram(program);

    return program;
}

ShaderSource Shader::ShaderParse(const std::string& filePath)
{
    enum ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT =1
    };

    std::ifstream stream(filePath);
    std::string line;
    std::stringstream ss[2];

    ShaderType type=ShaderType::NONE;

    while(std::getline(stream,line))
    {
        if(line.find("#shader")!=std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
            {
                type=ShaderType::VERTEX;
            }
            else if(line.find("fragment")!=std::string::npos)
            {
                type=ShaderType::FRAGMENT;
            }
        }
        else 
        {
            ss[(int)type]<<line<<"\n";
        }
    }
    return {ss[0].str(),ss[1].str()};
}

void Shader::SetUniform1i(const std::string name, int value)
{
    glUniform1i(GetUniformLocation(name),value);
}

void Shader::SetUniform1f(const std::string name, float value)
{
    glUniform1f(GetUniformLocation(name),value);
}

void Shader::SetUniform2f(const std::string name, float v1, float v2)
{
    glUniform2f(GetUniformLocation(name),v1,v2);
}

void Shader::SetUniform3f(const std::string name, float v1, float v2, float v3)
{
    glUniform3f(GetUniformLocation(name),v1,v2,v3);
}

void Shader::SetUniform4f(const std::string name, float v1, float v2, float v3, float v4)
{
    glUniform4f(GetUniformLocation(name),v1,v2,v3,v4);
}

void Shader::SetUniformMat3f(const std::string &name, const glm::mat3 &matrix)
{
    glUniformMatrix3fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]);
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix)
{
        glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string &name)
{
    if(m_Locations.find(name)!=m_Locations.end()) return m_Locations[name];
    int location=glGetUniformLocation(m_RendererID,name.c_str());
    if(location==-1) std::cout<<"[WARNING]The location"<<location<<"is not exist!"<<std::endl;
    else m_Locations[name]=location;
    return location;
}
