#pragma once
#include <string>
#include "kmint/pigisland/algorithms/finitestate/shark/SharkTired.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"

namespace kmint {
    namespace pigisland {
        class shark;

        namespace finitestate {
            class SharkGlobalState : public IState<shark>
            {
            private:
                int steps;
            public:
                void entry(shark& entity) override;
                void execute(shark& entity) override;
                void exit(shark& entity) override;
                std::string toString() override { return "SharkGlobal"; };
            };
        }
    }
}