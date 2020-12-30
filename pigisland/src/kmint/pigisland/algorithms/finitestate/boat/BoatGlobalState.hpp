#pragma once
#include "kmint/pigisland/algorithms/finitestate/boat/BoatRepair.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatGlobalState : public IState<boat>
            {
            private:
                bool repair = false;
                int steps = 0;
            public:
                virtual ~BoatGlobalState() {}

                void entry(boat& entity) override;
                void exit(boat& entity) override;
                void execute(boat& entity) override;
                std::string toString() override { return "BoatGlobal"; };
            };
        }
    }
}