#include "Test.h"
#include "../Renderer.h"
namespace test
{
    class TestClearColor:public Test
    {
        private:
            float m_ClearColor[4];

        public:
            TestClearColor();
            ~TestClearColor(){}

            void OnRender();
            void OnUpdate(float deltaTime);
            void OnImguiRender();
    };
}