#include "BoatWander.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatWander::entry(boat* entity) { entity->setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void BoatWander::exit(boat* entity) { entity->removeTint(); };

            void BoatWander::execute(boat* entity) {
                int next_index = random_int(0, entity->node().num_edges());
                entity->node(entity->node()[next_index].to());
            };

            std::string BoatWander::getState() { return "SharkWander"; };
        }
    }
}