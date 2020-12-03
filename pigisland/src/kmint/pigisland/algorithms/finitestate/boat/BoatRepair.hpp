#pragma once
#include "BoatState.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            class BoatRepair : public BoatState
            {
            public:
                ~BoatRepair() {}

                void entry(boat* entity) override;
                void execute(boat* entity) override;
                void exit(boat* entity) override;

                std::string getState() override;
            };
        }
    }
}