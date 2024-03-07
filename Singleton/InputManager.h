#include "Singleton.h"
#include "../DependencyManager.h"

namespace OWL
{
    namespace global
    {
         /*此单例统一管理所有的输入配置*/
        class InputManager:public Singleton<InputManager>
        {
            public:
                InputManager(){}
                ~InputManager(){}
                
        };
          

              
    }
    
   
}
