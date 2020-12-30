#pragma once
#include <queue>
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

#define MIN_DOCK_1 30
#define MAX_DOCK_1 50
#define MIN_DOCK_2 20
#define MAX_DOCK_2 100
#define DOCK_3 50

namespace kmint {
    namespace pigisland {
        class boat;
        namespace finitestate {
            class BoatRepair : public IState<boat>
            {
            public:
                ~BoatRepair() {}

                void entry(boat& entity) override;
                void execute(boat& entity) override;
                void exit(boat& entity) override;

                std::string toString() override;
            private:
                int chosenDock;
                std::queue<int> path;

                searchStrategy::PathFinder pathFinder;
                std::unique_ptr<searchStrategy::AStarSearchStrategy> astar;
            };
        }
    }
}