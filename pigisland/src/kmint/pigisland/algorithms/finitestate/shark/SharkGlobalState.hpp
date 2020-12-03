#pragma once
#include <string>
#include "SharkTired.hpp"

#define STEPS_REQUIRED_TIRED 100

namespace kmint {
    namespace pigisland {
        class shark;

        namespace finitestate {
            class SharkGlobalState
            {
            public:
                virtual ~SharkGlobalState() {}

                virtual void execute(shark* entity);
                virtual std::string getState();
            };
        }
    }
}