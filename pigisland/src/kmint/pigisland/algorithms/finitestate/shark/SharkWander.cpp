#include "SharkWander.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkWander::entry(shark* entity) { entity->setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void SharkWander::exit(shark* entity) { entity->removeTint(); };

            void SharkWander::execute(shark* entity) {
                if (entity->shouldFlee()) {
                    entity->getStateMachine().changeState(new SharkFlee, entity);
                }
                for (std::size_t i = 0; i < entity->num_perceived_actors(); ++i) {
                    kmint::play::actor& a = entity->perceived_actor(i);

                    // TODO check boat or pig
                    // pig;
                        // TODO If pig hit; remove pig
                    if (!a.removed()) {
                        entity->getStateMachine().changeState(new SharkChase, entity);
                        return;
                    }
                }
                entity->moveRandomly();
                entity->eatPig();
            };

            std::string SharkWander::toString() { return "SharkWander"; };
        }
    }
}