#include "Camera.h"

namespace OWL
{
    class FreeCamera:public Camera
    {
        private:
            //基本参数
            Transform m_Transform;
            glm::vec3 m_TargetDir;//目标朝向
            glm::vec3 m_UpDir;//上轴
            glm::vec3 m_RightDir;//右轴

            //自由摄像机需要的变量
            float yaw;
            float pitch;
            float sensitivity;

        public:
            FreeCamera();
            ~FreeCamera();
            void Start();
            void Update(float deltaTime);
    };
}