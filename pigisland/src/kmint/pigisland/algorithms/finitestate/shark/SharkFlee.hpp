#pragma once
#include "SharkState.hpp"
#include "SharkWander.hpp"
#include "SharkTired.hpp"
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"

#define MAX_STEPS 10

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            class SharkFlee : public SharkState
            {
            private:
                int steps = 0;
            public:
                virtual ~SharkFlee() {}

                void entry(shark* entity) override;
                void execute(shark* entity) override;
                void exit(shark* entity) override;

                std::string getState() override;
            };
        }
    }
}