#pragma once
#include <string>
#include "BoatRepair.hpp"
#define MAX_PAINT_DAMAGE 100

namespace kmint {
    namespace pigisland {
        class boat;

        namespace finitestate {
            class BoatGlobalState
            {
            public:
                virtual ~BoatGlobalState() {}

                void execute(boat* entity);
                std::string getState();
            };
        }
    }
}