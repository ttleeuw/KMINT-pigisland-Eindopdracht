#pragma once
#include "ISearchStrategy.hpp"

namespace searchStrategy {
    class PathFinder {
    public:
        void search(int source, int target, ISearchStrategy* strategy) {
            strategy->search(source, target);
        }
    };
}