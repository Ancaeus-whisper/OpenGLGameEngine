#include "Camera.h"

namespace OWL
{
    Camera::Camera():m_Transform({glm::vec3(0.0f,0.0f,3.0f),glm::vec3(1.0f,1.0f,1.0f),glm::vec3(0.0f,0.0f,0.0f)}),m_TargetPos(0,0,-1),m_UpDir(0,1,0)
    {
        Object::Active(true);
    }
    Camera::~Camera()
    {
    }
    void Camera::Start()
    {
    }
    void Camera::Update(float deltaTime)
    {

    }
    void Camera::SetTargetPos(glm::vec3 target)
    {
        m_TargetPos=target;
        SetCameraDirection();
    }
    void Camera::SetCameraDirection()
    {
        m_TargetDir=glm::normalize(m_Transform.position-m_TargetPos);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
        m_RightDir = glm::normalize(glm::cross(up, m_TargetDir));
        m_UpDir = glm::cross(m_TargetDir, m_RightDir);    
    }
    glm::mat4 Camera::LookAt() const
    {
        return glm::lookAt(m_Transform.position,m_TargetDir,m_UpDir);
    }
}