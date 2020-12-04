#pragma once
#include <string>
#include "kmint/pigisland/algorithms/finitestate/shark/SharkTired.hpp"
#include "kmint/pigisland/algorithms/finitestate/IGlobalState.hpp"

namespace kmint {
    namespace pigisland {
        class shark;

        namespace finitestate {
            class SharkGlobalState : public IGlobalState<shark>
            {
            public:
                void execute(shark* entity) override;
                std::string toString() override;
            };
        }
    }
}