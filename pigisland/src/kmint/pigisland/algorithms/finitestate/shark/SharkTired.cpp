#include "SharkTired.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkTired::entry(shark* entity) {
                entity->setTint(kmint::graphics::color(204, 255, 230, 0));

                astar = std::make_unique<searchStrategy::AStarSearchStrategy>(entity->getGraph());
                pathFinder.search(entity->node().node_id(), entity->getInitialNode().node_id(), astar.get());
                this->path = astar->getShortestPath();
            };

            void SharkTired::execute(shark* entity) {
                if (!path.empty()) {
                    auto next = path.front();
                    path.pop();
                    for (size_t i = 0; i < entity->node().num_edges(); i++)
                    {
                        if (entity->node()[i].to().node_id() == next) {
                            entity->node(entity->node()[i].to());
                        }
                    }
                }
                else {
                    entity->setResting(true);
                }
            };

            void SharkTired::exit(shark* entity) {  entity->removeTint(); };

            std::string SharkTired::toString() { return "SharkReturn"; };
        }
    }
}