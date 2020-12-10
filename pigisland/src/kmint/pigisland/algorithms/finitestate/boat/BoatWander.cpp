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
                // TODO remove if pig, PIG saved
                for (std::size_t i = 0; i < entity->num_colliding_actors(); ++i)
                {
                    auto& a = entity->colliding_actor(i);
                    a.remove();
                }
            };

            std::string BoatWander::toString() { return "BoatWander"; };
        }
    }
}