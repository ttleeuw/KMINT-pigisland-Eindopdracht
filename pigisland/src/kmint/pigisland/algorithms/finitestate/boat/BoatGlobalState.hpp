#pragma once
#include "kmint/pigisland/algorithms/finitestate/boat/BoatRepair.hpp"
#include "kmint/pigisland/algorithms/finitestate/IGlobalState.hpp"

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatGlobalState : public IGlobalState<boat>
            {
            private:
                bool repair = false;
            public:
                virtual ~BoatGlobalState() {}

                void execute(boat* entity) override;
            };
        }
    }
}