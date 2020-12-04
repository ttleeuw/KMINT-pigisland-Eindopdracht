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

            if (nextClosestNode == _target) break;

            for (std::size_t i = 0; i < _graph[nextClosestNode].num_edges(); ++i) {
                auto edge = &_graph[nextClosestNode][i];
                if (edge->to().tagged()) continue;

                double heuristicCost = calculateHeuristicCosts(edge, _target);
                double calculatedRealCost = _realCosts[nextClosestNode] + edge->weight();

                //if the node has not been added to the frontier, add it and update the G and F costs
                auto nodeId = edge->to().node_id();
                if (_searchFrontier[nodeId] == NULL)
                {
                    _estimatedCosts[nodeId] = calculatedRealCost + heuristicCost;
                    _realCosts[nodeId] = calculatedRealCost;
                    priorityQueue.insert(nodeId, calculatedRealCost + heuristicCost);
                    _searchFrontier[nodeId] = edge;
                }
                //if this node is already on the frontier but the cost to get here is cheaper than has been found previously, update the node costs and frontier accordingly.
                else if ((calculatedRealCost < _realCosts[nodeId]) && (_shortestPathTree[nodeId] == NULL))
                {
                    _estimatedCosts[nodeId] = calculatedRealCost + heuristicCost;
                    _realCosts[nodeId] = calculatedRealCost;
                    _searchFrontier[nodeId] = edge;
                }
            }
        }

        std::queue<int> path;

        if (_target < 0) {
            shortestPath = path;
            return;
        }

        int current = _target;
        path.push(current);
        while ((current != _source) && (_shortestPathTree[current] != 0))
        {
            _graph[current].tag(kmint::graph::node_tag::path);
            current = _shortestPathTree[current]->from().node_id();
            path.push(current);
        }

        std::vector<int> stack;
        while (!path.empty()) {
            stack.push_back(path.front());
            path.pop();
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