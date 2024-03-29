#include "TestClearColor.h"

namespace test{
TestClearColor::TestClearColor():m_ClearColor{0.2f,0.3f,0.4f,1.0f}
{
}

void TestClearColor::OnRender()
{
    GLCALL(glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnUpdate(float deltaTime)
{
}

void TestClearColor::OnImguiRender()
{
    ImGui::ColorEdit4("ClearColor",m_ClearColor);
}
}