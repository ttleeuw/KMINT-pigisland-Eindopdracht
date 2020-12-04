#pragma once
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkTired.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"

#define MAX_STEPS 10

namespace kmint {
    namespace pigisland {
        class shark;
        namespace finitestate {
            class SharkFlee : public IState<shark>
            {
            private:
                int steps = 0;
            public:
                virtual ~SharkFlee() {}

                void entry(shark* entity) override;
                void execute(shark* entity) override;
                void exit(shark* entity) override;

                std::string toString() override;
            };
        }
    }
}