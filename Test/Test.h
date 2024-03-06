#pragma once
#include <imgui/imgui.h>
#include <vector>
#include <functional>
#include <string>

namespace test{
/*
类型说明
类名:Test 种类:基类
实现功能：
    OnUpdate:
        主循环中的运动逻辑
    OnRender:
        渲染部分
    OnImguiRender:
        UI渲染
*/
class Test
{
    public:
        Test(){}
        virtual ~Test(){}

        virtual void OnUpdate(float deltaTime){}
        virtual void OnRender(){}
        virtual void OnImguiRender(){}
};

class TestMenu:public Test
{
    private:
        Test*& m_currentTest;
        std::vector<std::pair<std::string,std::function<Test*()>>> m_tests;

    public:
        TestMenu(Test*& currentTestPointer);
        ~TestMenu(){}

        void OnImguiRender();

        template<typename T> void RegisterTest(const std::string& name);
};
    template<typename T> 
    inline void TestMenu::RegisterTest(const std::string& name)
    {
        m_tests.push_back(std::make_pair(name,[](){return new T();}));
    }

}
