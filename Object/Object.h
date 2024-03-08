#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
namespace OWL{
struct Transform
{
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotate;
};

class Object
{
    private:
        //基本参数
        Transform m_Transform;

        bool m_Active;

        unsigned int m_ObjectID;
        Object* m_parent; //Object的父节点
        std::vector<std::pair<std::string,Object*>> m_Children;//Object的子节点
        
    public:
        Object(){}
        virtual ~Object(){}
        virtual void Start(){}
        virtual void Update(float deltaTime){}
        
        int GetID()const{return m_ObjectID;}
        bool IsActive()const{return m_Active;}

        void Active(bool value){m_Active=value;}

        void AddChild(const std::string& name,Object* child)
        {
            m_Children.push_back(std::make_pair(name,child));
        }
        void SetParent(Object* const parent){m_parent=parent;}

        //XXX 还不确定transform的值是否可以在外部修改，如有必要请修改定义
        Transform* GetTransform(){return &m_Transform;}
};
}