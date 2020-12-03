#include "SharkFlee.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkFlee::entry(shark* entity) { entity->setTint(kmint::graphics::color(25, 255, 140, 0)); };
            void SharkFlee::exit(shark* entity) { entity->removeTint(); };

            void SharkFlee::execute(shark* entity) {
                int next_index = random_int(0, entity->node().num_edges());
                entity->node(entity->node()[next_index].to());
                steps++;
                if (steps == MAX_STEPS) {
                    entity->changeState(new SharkWander);
                }
            };

            std::string SharkFlee::getState() { return "SharkFlee"; };
        }
    }
}