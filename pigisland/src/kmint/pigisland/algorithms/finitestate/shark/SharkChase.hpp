#pragma once
#include "SharkState.hpp"
#include "SharkWander.hpp"
#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "SharkTired.hpp"
#include <queue>

#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            class SharkChase : public SharkState
            {
            public:
                SharkChase() { }
                virtual ~SharkChase() {}

                void entry(shark* entity) override;
                void execute(shark* entity) override;
                void exit(shark* entity) override;

                std::string getState() override;
            private:
                std::queue<int> path;

                searchStrategy::PathFinder pathFinder;
                std::unique_ptr<searchStrategy::AStarSearchStrategy> astar;
            };
        }
    }
}