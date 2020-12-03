#pragma once
#include <list>
#include <vector>
#include <queue>

#include <kmint/graph/basic_node.hpp>
#include <kmint/graph/graph.hpp>
#include <kmint/map/map.hpp>

namespace searchStrategy {
    class ISearchStrategy {
    protected:
        kmint::map::map_graph& _graph;
        int _source;
        int _target;
    public:
        ISearchStrategy(kmint::map::map_graph& graph) : _graph(graph), _source(-1), _target(-1) { }
        virtual void search(int source, int target) = 0;
        virtual std::vector <const kmint::graph::basic_edge<kmint::map::map_node_info>*> getVisited() const = 0;
        virtual std::queue<int> getShortestPath() const = 0;
        virtual double getCost() const = 0;
    };
}