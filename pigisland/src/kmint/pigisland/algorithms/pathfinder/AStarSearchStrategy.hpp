#pragma once

#include "ISearchStrategy.hpp"
#include <kmint/pigisland/datastructures/PriorityQueue.hpp>

#define PIXEL_COST 32

namespace searchStrategy {
    using edge = kmint::graph::basic_edge<kmint::map::map_node_info>;
    using mGraph = kmint::map::map_graph;

    class AStarSearchStrategy : public ISearchStrategy
    {
    public:
        AStarSearchStrategy(mGraph& graph);

        void search(int source, int target);

        std::vector <const edge*> getVisited() const;
        std::queue<int> getShortestPath() const;
        double getCost() const;
    private:
        std::queue<int> shortestPath;
        std::vector<double> _realCosts;
        std::vector<double> _estimatedCosts;
        std::vector<const edge*> _shortestPathTree;
        std::vector<const edge*> _searchFrontier;

        double calculateHeuristicCosts(const edge* edge, int target);
        void searchAStar();
        void initSearch();
    };
}