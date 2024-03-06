#include "Test.h"

test::TestMenu::TestMenu(Test*& currentTestPointer):m_currentTest(currentTestPointer)
{
}


void test::TestMenu::OnImguiRender()
{
    for(auto& test:m_tests)
    {
        if(ImGui::Button(test.first.c_str()))
        {
            m_currentTest=test.second();
        }
    }
}
