#include "SharkWander.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkWander::entry(shark* entity) { entity->setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void SharkWander::exit(shark* entity) { entity->removeTint(); };

            void SharkWander::execute(shark* entity) {
                // laat ook even zien welke varkentjes hij ruikt
                for (std::size_t i = 0; i < entity->num_perceived_actors(); ++i) {
                    auto& a = entity->perceived_actor(i);

                    // TODO check boat or pig
                    // pig;
                    if (!a.removed()) {
                        entity->changeState(new SharkChase);
                        return;
                    }    
                    // boat;
                        //entity->changeState(new SharkFlee);
                        //return;

                   // }
                }
                // TODO If pig hit; remove pig
                int next_index = random_int(0, entity->node().num_edges());
                entity->node(entity->node()[next_index].to());
            };

            std::string SharkWander::getState() { return "SharkWander"; };
        }
    }
}