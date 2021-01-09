#include "AStarSearchStrategy.hpp"

namespace searchStrategy {
    AStarSearchStrategy::AStarSearchStrategy(mGraph& graph) : ISearchStrategy(graph) { }

    void AStarSearchStrategy::search(int source, int target)
    {
        _source = source;
        _target = target;
        initSearch();
        searchAStar();
    }

    std::vector <const edge*> AStarSearchStrategy::getVisited() const { return _shortestPathTree; }
    std::queue<int> AStarSearchStrategy::getShortestPath() const { return shortestPath; }
    double AStarSearchStrategy::getCost() const { return _realCosts[_target]; }

    // Eucliedian distance
    double AStarSearchStrategy::calculateHeuristicCosts(const edge* edge, int target) {
        auto dx = edge->to().location().x() - _graph[target].location().x();
        auto dy = edge->to().location().y() - _graph[target].location().y();
        auto costs = sqrt((double)dx * dx + (double)dy * dy);
        return costs / PIXEL_COST;
    }

    void AStarSearchStrategy::searchAStar() {
        PriorityQueue<int, double> priorityQueue;
        priorityQueue.insert(_source, 0);

        while (!priorityQueue.empty())
        {
            int nextClosestNode = priorityQueue.pop();
            _graph[nextClosestNode].tag(kmint::graph::node_tag::visited);
            _shortestPathTree[nextClosestNode] = _searchFrontier[nextClosestNode];
            // at the target position
            if (nextClosestNode == _target) break;
            // Loop over the edges
            for (std::size_t i = 0; i < _graph[nextClosestNode].num_edges(); ++i) {
                auto edge = &_graph[nextClosestNode][i];
                if (edge->to().tagged()) continue;

                double heuristicCost = calculateHeuristicCosts(edge, _target);
                double calculatedRealCost = _realCosts[nextClosestNode] + edge->weight();

                auto nodeId = edge->to().node_id();
                // Node hasnt been added
                if (_searchFrontier[nodeId] == NULL)
                {
                    _estimatedCosts[nodeId] = calculatedRealCost + heuristicCost;
                    _realCosts[nodeId] = calculatedRealCost;
                    priorityQueue.insert(nodeId, calculatedRealCost + heuristicCost);
                    _searchFrontier[nodeId] = edge;
                }
                // Cheaper to get here than previously found
                else if ((calculatedRealCost < _realCosts[nodeId]) && (_shortestPathTree[nodeId] == NULL))
                {
                    _estimatedCosts[nodeId] = calculatedRealCost + heuristicCost;
                    _realCosts[nodeId] = calculatedRealCost;
                    _searchFrontier[nodeId] = edge;
                }
            }
        }

        // Traceback
        std::queue<int> path;

        if (_target < 0) {
            shortestPath = path;
            return;
        }
        std::vector<int> stack;
        int current = _target;
        stack.push_back(current);
        while ((current != _source) && (_shortestPathTree[current] != 0))
        {
            _graph[current].tag(kmint::graph::node_tag::path);
            current = _shortestPathTree[current]->from().node_id();
            stack.push_back(current);
        }

        while (!stack.empty()) {
            path.push(stack.back());
            stack.pop_back();
        }

        int i = path.front();
        path.pop();
        shortestPath = path;
    }

    void AStarSearchStrategy::initSearch() {
        _realCosts = std::vector<double>(_graph.num_nodes(), 0.0);
        _estimatedCosts = std::vector<double>(_graph.num_nodes(), 0.0);
        _shortestPathTree = std::vector<const edge*>(_graph.num_nodes());
        _searchFrontier = std::vector<const edge*>(_graph.num_nodes());
        _graph.untag_all();
    }
}