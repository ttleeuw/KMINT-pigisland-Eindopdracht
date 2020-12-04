#pragma once
#include <string>
#include "kmint/pigisland/algorithms/finitestate/IGlobalState.hpp"
#include "kmint/pigisland/algorithms/finitestate/boat/BoatRepair.hpp"

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatGlobalState : public IGlobalState<boat>
            {
            public:
                virtual ~BoatGlobalState() {}

                void execute(boat* entity) override;
                std::string toString() override;
            };
        }
    }
}