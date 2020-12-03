#ifndef PIGISLAND_NODE_ALGORITHM_HPP
#define PIGISLAND_NODE_ALGORITHM_HPP

#include "kmint/map/map.hpp"
namespace kmint {
    namespace pigisland {
        /// Gets the number of periods for which an entity has to wait before it can move to an adjacent node
        double waiting_time(map::map_node const &node);

        /// Finds a random node adjacent to argument node
        map::map_node const &random_adjacent_node(map::map_node const &node);

        /// Finds a node of a given kind (which is the character by which it is represented textually)
        ///
        /// You must take care that a node of the given kind exists. Otherwise the behaviour of this function is undefined.
        map::map_node const &find_node_of_kind(map::map_graph const &graph, char kind);

        /// Finds a node of a given kind (which is the character by which it is represented textually)
        ///
        /// You must take care that a node of the given kind exists. Otherwise the behaviour of this function is undefined.
        map::map_node &find_node_of_kind(map::map_graph &graph, char kind);

        /// Finds a random mooring place for the boat
        map::map_node const &find_random_mooring_place(map::map_graph const &graph);

        /// Find the shark's resting place.
        map::map_node const &find_shark_resting_place(map::map_graph const &graph);

        /// Finds the closest node to a location
        map::map_node const &find_closest_node_to(map::map_graph const &graph, math::vector2d location);
    } // namespace pigisland
} // namespace kmint

#endif /* PIGISLAND_NODE_ALGORITHM_HPP */
