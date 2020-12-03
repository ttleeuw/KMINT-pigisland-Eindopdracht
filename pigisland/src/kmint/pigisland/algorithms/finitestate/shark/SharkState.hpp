#pragma once

#include <string>

namespace kmint {
    namespace pigisland {
        class shark;

        namespace finitestate {
            class SharkState
            {
            public:
                virtual ~SharkState() {}

                virtual void entry(shark* entity) = 0;
                virtual void execute(shark* entity) = 0;
                virtual void exit(shark* entity) = 0;

                virtual std::string getState() = 0;
            };
        }
    }
}