#include <iostream>

#include "kmint/pigisland/entities/base/MapActor.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        MapActor::MapActor(map::map_graph& g, map::map_node& initial_node, play::actor const& owner, graphics::image image)
            : play::map_bound_actor{ initial_node }, graph(g), initial(initial_node), drawable_{ owner, image }
        {
        }
        void MapActor::moveRandomly()
        {
            canMove = waitIfNecessary();
            if (canMove) {
                int next_index = random_int(0, this->node().num_edges());
                waitTimer = this->node()[next_index].weight() - 1;
                this->node(this->node()[next_index].to());
            }
        }

        void MapActor::moveWithPath(std::queue<int>& path)
        {
            canMove = waitIfNecessary();
            if (!path.empty() && canMove) {
                auto next = path.front();
                path.pop();
                for (size_t i = 0; i < this->node().num_edges(); i++)
                {
                    if (this->node()[i].to().node_id() == next) {
                        waitTimer = this->node()[i].weight() - 1;
                        this->node(this->node()[i].to());
                        break;
                    }
                }
            }
        }

        bool MapActor::waitIfNecessary()
        {
            if (waitTimer <= 0) {
                return true;
            }
            waitTimer--;
            return false;
        }
    } // namespace pigisland
} // namespace kmint
