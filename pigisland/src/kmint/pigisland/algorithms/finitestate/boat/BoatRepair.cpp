#include "BoatRepair.hpp"
#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatRepair::entry(boat* entity) {
                entity->setTint(kmint::graphics::color(128, 128, 255, 0)); 

				const int random_number = random_int(0, 3);
                astar = std::make_unique<searchStrategy::AStarSearchStrategy>(entity->getGraph());
                
                // TODO Probabilistic finite state machines
				if (random_number)
				{
                    pathFinder.search(entity->node().node_id(), find_node_of_kind(entity->getGraph(), '1').node_id(), astar.get());
                    path = astar->getShortestPath();
				}
				else if (random_number)
				{
                    pathFinder.search(entity->node().node_id(), find_node_of_kind(entity->getGraph(), '2').node_id(), astar.get());
                    path = astar->getShortestPath();
				}
				else
				{
                    pathFinder.search(entity->node().node_id(), find_node_of_kind(entity->getGraph(), '3').node_id(), astar.get());
                    path = astar->getShortestPath();
				}

            };

            void BoatRepair::exit(boat* entity) {
                // TODO
                //entity->removeTint(); 
            };

            void BoatRepair::execute(boat* entity) {
                // TODO
            };

            std::string BoatRepair::toString() { return "BoatRepair"; };
        }
    }
}