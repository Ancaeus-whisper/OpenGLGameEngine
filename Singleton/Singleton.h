#pragma once
#include <memory>
#include <mutex>
#include <iostream>
namespace OWL
{
    namespace global
    {
        template<typename T>
        class Singleton
        {
            public:
                static T* getInstance()
                {
                    static std::once_flag s_flag;
                    std::call_once(s_flag,[&](){
                        m_Instance.reset(new T());
                    });
                    return m_Instance.get();
                }

                void Address()const
                {
                    std::cout<<this<<std::endl;
                }

            protected:
                Singleton(){}
                ~Singleton(){}
                
                static std::shared_ptr<T> m_Instance;
            private:
                Singleton(const Singleton&)=delete;
                Singleton& operator=(const Singleton&)=delete;
                
        };

        template<typename T> std::shared_ptr<T> Singleton<T>::m_Instance;
    }
}