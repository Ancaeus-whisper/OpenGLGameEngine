#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>

namespace OWL{
class Camera:public Object
{
    private:
        //XXX Object池构建后需要重构摄像机逻辑，具体来说需要一个看向的对象
        //基本参数
        Transform m_Transform;
        glm::vec3 m_TargetDir;//目标朝向
        glm::vec3 m_UpDir;//上轴
        glm::vec3 m_RightDir;//右轴
        
    public:
        Camera();
        ~Camera();
        void Start();
        void Update(float deltaTime);

        void SetCameraDirection(glm::vec3 target);
        glm::mat4 LookAt()const;
};
}