#include "BoatRepair.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatRepair::entry(boat* entity) {
                // TODO
                //entity->setTint(kmint::graphics::color(128, 128, 255, 0)); 
            };

            void BoatRepair::exit(boat* entity) {
                // TODO
                //entity->removeTint(); 
            };

            void BoatRepair::execute(boat* entity) {
                // TODO
            };

            std::string BoatRepair::getState() { return "SharkWander"; };
        }
    }
}