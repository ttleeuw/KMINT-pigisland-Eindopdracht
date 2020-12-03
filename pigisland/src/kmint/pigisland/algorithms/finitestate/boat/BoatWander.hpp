#pragma once
#include "BoatState.hpp"
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            class BoatWander : public BoatState
            {
            public:
                void entry(boat* entity) override;
                void execute(boat* entity) override;
                void exit(boat* entity) override;

                std::string getState() override;
            };
        }
    }
}