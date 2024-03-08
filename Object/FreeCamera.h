#pragma once
#include "Camera.h"
#include "../Singleton/WindowManager.h"

namespace OWL
{
    
    class FreeCamera:public Camera
    {
        private:

            //自由摄像机需要的变量
            float yaw;
            float pitch;
            float sensitivity;

            float lastX;
            float lastY;

            bool firstMouse;

            void handleMouse();
            void handleKeyboard(float deltaTime);
        public:
            FreeCamera();
            ~FreeCamera();
            void Start();
            void Update(float deltaTime);
            
    };
}