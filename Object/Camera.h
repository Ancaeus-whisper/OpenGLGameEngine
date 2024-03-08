#pragma once
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace OWL{
//XXX 缺陷良多，仅限够用，时间关系，暂且放着，以后再改
class Camera:public Object
{
    protected:
        //XXX Object池构建后需要重构摄像机逻辑，具体来说需要一个看向的对象
        //基本参数
        Transform m_Transform;
        glm::vec3 m_TargetPos;
        glm::vec3 m_TargetDir;//目标朝向
        glm::vec3 m_UpDir;//上轴
        glm::vec3 m_RightDir;//右轴
        
    public:
        Camera();
        ~Camera();
        void Start();
        void Update(float deltaTime);

        void SetTargetPos(glm::vec3 target);
        void SetCameraDirection();
        glm::mat4 LookAt()const;
        glm::vec3 GetTarget()const{return m_TargetPos;}
};
}