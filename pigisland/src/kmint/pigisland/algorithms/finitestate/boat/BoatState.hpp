#pragma once
#include <string>

namespace kmint {
    namespace pigisland {
        class boat; 

        namespace finitestate {
            class BoatState
            {
            public:
                virtual ~BoatState() {}

                virtual void entry(boat* entity) = 0;
                virtual void execute(boat* entity) = 0;
                virtual void exit(boat* entity) = 0;

                virtual std::string getState() = 0;
            };
        }
    }
}