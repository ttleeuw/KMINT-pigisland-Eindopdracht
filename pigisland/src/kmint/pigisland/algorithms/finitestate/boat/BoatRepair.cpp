#include "BoatRepair.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatRepair::entry(boat* entity) {
                entity->setTint(kmint::graphics::color(255, 0, 0, 0)); 

                chosenDock = random_int(1, 4);
                astar = std::make_unique<searchStrategy::AStarSearchStrategy>(entity->getGraph());
                // TODO Probabilistic finite state machines
                pathFinder.search(entity->node().node_id(), find_node_of_kind(entity->getGraph(), std::to_string(chosenDock)[0]).node_id(), astar.get());
                path = astar->getShortestPath();
            };

            void BoatRepair::execute(boat* entity) {
                if (!path.empty() && entity->waitIfNecessary()) {
                    entity->moveWithPath(path);
                    // Save
                    entity->savePig();
                }
                else if (path.empty()) {
                    entity->getStateMachine().changeState(new BoatWander, entity);
                }
            };

            void BoatRepair::exit(boat* entity) {

                switch (chosenDock)
                {
                case 1:
                    entity->repair((DockingStation)chosenDock, random_int(MIN_DOCK_1, MAX_DOCK_1));
                    break;
                case 2:
                    entity->repair((DockingStation)chosenDock, random_int(MIN_DOCK_2, MAX_DOCK_2));
                    break;
                case 3:
                    entity->repair((DockingStation)chosenDock, DOCK_3);
                    break;
                default:
                    break;
                }
                entity->getGraph().untag_all();
                entity->removeTint();
            };

            std::string BoatRepair::toString() { return "BoatRepair"; };
        }
    }
}