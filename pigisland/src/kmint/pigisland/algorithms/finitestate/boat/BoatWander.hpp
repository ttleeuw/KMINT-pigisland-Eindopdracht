#pragma once
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatWander : public IState<boat>
            {
            public:
                void entry(boat* entity) override;
                void execute(boat* entity) override;
                void exit(boat* entity) override;

                std::string toString() override;
            };
        }
    }
}