#include "SharkChase.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkChase::entry(shark* entity) {
                entity->setTint(kmint::graphics::color(255, 25, 25, 0));

                astar = std::make_unique<searchStrategy::AStarSearchStrategy>(entity->getGraph());

                for (std::size_t i = 0; i < entity->num_perceived_actors(); ++i) {
                    auto& a = entity->perceived_actor(i);
                    
                    map::map_node* node = &entity->getGraph()[0];
                    std::for_each(entity->getGraph().begin(), entity->getGraph().end(), [&](map::map_node& n) {
                        if (math::distance(n.location(), a.location()) < math::distance(node->location(), a.location())) node = &n;
                    });
                    pathFinder.search(entity->node().node_id(), node->node_id(), astar.get());
                    this->path = astar->getShortestPath();
                    return;
                }
            };

            void SharkChase::execute(shark* entity) {
                // TODO; Check should flee
                if (!path.empty()) {
                    auto next = path.front();
                    path.pop();
                    for (size_t i = 0; i < entity->node().num_edges(); i++)
                    {
                        if (entity->node()[i].to().node_id() == next) {
                            entity->node(entity->node()[i].to());
                            break;
                        }
                    }

                    for (std::size_t i = 0; i < entity->num_colliding_actors(); ++i)
                    {
                        auto& a = entity->colliding_actor(i);
                        // TODO remove
                        a.remove();
                    }
                }
                else {
                    entity->changeState(new SharkWander);
                }
            };

            void SharkChase::exit(shark* entity) {
                entity->getGraph().untag_all();
                entity->removeTint();
            };

            std::string SharkChase::getState() { return "SharkChase"; };
        }
    }
}