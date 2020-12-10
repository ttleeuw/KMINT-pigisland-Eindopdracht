#pragma once
#include <string>

#define STEPS_REQUIRED 100

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            template <typename T>
            class IGlobalState
            {
            public:
                virtual void execute(T* entity) = 0;
            };
        }
    }
}