#pragma once
#include <queue>
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatRepair : public IState<boat>
            {
            public:
                ~BoatRepair() {}

                void entry(boat* entity) override;
                void execute(boat* entity) override;
                void exit(boat* entity) override;

                std::string toString() override;
            private:
                std::queue<int> path;

                searchStrategy::PathFinder pathFinder;
                std::unique_ptr<searchStrategy::AStarSearchStrategy> astar;
            };
        }
    }
}