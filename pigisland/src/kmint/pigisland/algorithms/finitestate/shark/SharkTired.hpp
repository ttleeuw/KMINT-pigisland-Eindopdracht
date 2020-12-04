#pragma once
#include <queue>

#include "kmint/random.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

namespace kmint {
    namespace pigisland {
        class shark;

        namespace finitestate {
            class SharkTired : public IState<shark>
            {
            public:
                virtual ~SharkTired() {}

                void entry(shark* entity) override;
                void execute(shark* entity) override;
                void exit(shark* entity) override;

                std::string toString() override;
            private:
                std::queue<int> path;

                searchStrategy::PathFinder pathFinder;
                std::unique_ptr<searchStrategy::AStarSearchStrategy> astar;
            };
        }
    }
}