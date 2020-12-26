#pragma once
#include <queue>

#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/IState.hpp"
#include "kmint/pigisland/algorithms/pathfinder/PathFinder.hpp"
#include "kmint/pigisland/algorithms/pathfinder/AStarSearchStrategy.hpp"

namespace kmint {
    namespace pigisland {
        class shark;
        namespace finitestate {
            class SharkChase : public IState<shark>
            {
            public:
                SharkChase() { }
                virtual ~SharkChase() {}

                void entry(shark& entity) override;
                void execute(shark& entity) override;
                void exit(shark& entity) override;

                std::string toString() override;
            private:
                std::queue<int> path;

                searchStrategy::PathFinder pathFinder;
                std::unique_ptr<searchStrategy::AStarSearchStrategy> astar;
            };
        }
    }
}