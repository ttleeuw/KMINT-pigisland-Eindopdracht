#pragma once
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkTired.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkChase.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkFlee.hpp"

namespace kmint {
    namespace pigisland {
        class shark;
        namespace finitestate {
            class SharkWander : public IState<shark>
            {
            public:
                virtual ~SharkWander() {}

                void entry(shark& entity) override;
                void execute(shark& entity) override;
                void exit(shark& entity) override;

                std::string toString() override;
            };
        }
    }
}