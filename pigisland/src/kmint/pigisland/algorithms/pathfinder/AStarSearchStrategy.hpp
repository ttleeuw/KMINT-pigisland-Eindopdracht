#pragma once

#include "ISearchStrategy.hpp"
#include <kmint/pigisland/datastructures/PriorityQueue.hpp>

#define PIXEL_COST 32

namespace searchStrategy {
    class AStarSearchStrategy : public ISearchStrategy
    {
    public:
        AStarSearchStrategy(kmint::map::map_graph& graph);

        void search(int source, int target);

        std::vector <const kmint::graph::basic_edge<kmint::map::map_node_info>*> getVisited() const;
        std::queue<int> getShortestPath() const;
        double getCost() const;
    private:
        std::queue<int> shortestPath;
        std::vector<double> _realCosts;
        std::vector<double> _estimatedCosts;
        std::vector<const kmint::graph::basic_edge<kmint::map::map_node_info>*> _shortestPathTree;
        std::vector<const kmint::graph::basic_edge<kmint::map::map_node_info>*> _searchFrontier;

        double calculateHeuristicCosts(const kmint::graph::basic_edge<kmint::map::map_node_info>* edge, int target);
        void searchAStar();
        void initSearch();
    };
}