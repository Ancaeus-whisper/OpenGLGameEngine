#include "FreeCamera.h"
namespace OWL
{
    void FreeCamera::handleMouse()
    {
        double xPos, yPos;
        glfwGetCursorPos(global::WindowManager::getInstance()->GetWindow(), &xPos,&yPos);

        if(firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse=false;
        }

        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos; 
        lastX = xPos;
        lastY = yPos;

        sensitivity = 0.1;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
        //std::cout<<"yaw:"<<yaw<<"pitch:"<<pitch<<std::endl;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_TargetDir=glm::normalize(front);
        //XXX 世界坐标不一定是标准笛卡尔坐标系，坐标轴也不一定标准，一定要回来改！
        m_RightDir = glm::normalize(glm::cross(m_TargetDir, glm::vec3(0.0f, 1.0f, 0.0f)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_UpDir    = glm::normalize(glm::cross(m_RightDir, m_TargetDir));
        //std::cout<<"targetX:"<<m_TargetDir.x<<"targetY:"<<m_TargetDir.y<<"targetZ:"<<m_TargetDir.z<<std::endl;
        //Camera::SetCameraDirection();
    }

    void FreeCamera::handleKeyboard(float deltaTime)
    {
        if (glfwGetKey(global::WindowManager::getInstance()->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        global::WindowManager::getInstance()->Quit();

        float cameraSpeed = 2.5f * deltaTime;
        if (glfwGetKey(global::WindowManager::getInstance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            this->m_Transform.position += cameraSpeed * m_TargetDir;
        if (glfwGetKey(global::WindowManager::getInstance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
            this->m_Transform.position -= cameraSpeed * m_TargetDir;
        if (glfwGetKey(global::WindowManager::getInstance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            this->m_Transform.position -= glm::normalize(glm::cross(m_TargetDir, m_UpDir)) * cameraSpeed;
        if (glfwGetKey(global::WindowManager::getInstance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            this->m_Transform.position += glm::normalize(glm::cross(m_TargetDir, m_UpDir)) * cameraSpeed;

        //std::cout<<"positionX:"<<m_Transform.position.x<<"positionY"<<m_Transform.position.y<<"positionZ"<<m_Transform.position.z<<std::endl;
    }

    FreeCamera::FreeCamera():yaw(0.0f),pitch(0.0f),sensitivity(0.05f)
                            ,firstMouse(true),Camera(),lastX(global::WindowManager::getInstance()->GetWidth()/2.0f),lastY(global::WindowManager::getInstance()->GetHeight()/2.0f)
    {
        glfwSetInputMode(global::WindowManager::getInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }
    FreeCamera::~FreeCamera()
    {
        glfwSetInputMode(global::WindowManager::getInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR);

    }
    void FreeCamera::Start()
    {
        
    }
    void FreeCamera::Update(float deltaTime)
    {
        handleKeyboard(deltaTime);
        handleMouse();
    }
}