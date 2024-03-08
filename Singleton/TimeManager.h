#pragma once
#include "Singleton.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OWL
{
    namespace global
    {
        class TimeManager:public Singleton<TimeManager>
        {
            private:
                float deltaTime = 0.0f; // 当前帧与上一帧的时间差
                float lastFrame = 0.0f; // 上一帧的时间
            public:
                TimeManager(){}
                ~TimeManager(){}

                inline void Update()
                {
                    float currentFrame = glfwGetTime();
                    deltaTime = currentFrame - lastFrame;
                    lastFrame = currentFrame;
                }

                inline float getDeltaTime()const{return deltaTime;}
        };
    } // namespace global
    
} // namespace OWL
