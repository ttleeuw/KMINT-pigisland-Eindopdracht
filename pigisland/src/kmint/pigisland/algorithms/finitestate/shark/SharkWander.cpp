#include "SharkWander.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkWander::entry(shark* entity) { entity->setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void SharkWander::exit(shark* entity) { entity->removeTint(); };

            void SharkWander::execute(shark* entity) {
                // TODO check flee
                for (std::size_t i = 0; i < entity->num_perceived_actors(); ++i) {
                    kmint::play::actor& a = entity->perceived_actor(i);

                    // TODO check IF PIG
                    // TODO remove pig
                    if (!a.removed()) {
                        entity->getStateMachine().changeState(new SharkChase, entity);
                        return;
                    }    
                }
                int next_index = random_int(0, entity->node().num_edges());
                entity->node(entity->node()[next_index].to());
            };

            std::string SharkWander::toString() { return "SharkWander"; };
        }
    }
}