#include "SharkTired.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkTired::entry(shark& entity) {
                entity.setTint(kmint::graphics::color(204, 255, 230, 0));

                astar = std::make_unique<searchStrategy::AStarSearchStrategy>(entity.getGraph());
                pathFinder.search(entity.node().node_id(), entity.getInitialNode().node_id(), astar.get());
                this->path = astar->getShortestPath();
            };

            void SharkTired::execute(shark& entity) {
                if (!path.empty()) {
                    entity.moveWithPath(path);
                }
                else {
                    entity.setResting(true);
                }
            };

            void SharkTired::exit(shark& entity) { entity.removeTint(); };

            std::string SharkTired::toString() { return "SharkReturn"; };
        }
    }
}