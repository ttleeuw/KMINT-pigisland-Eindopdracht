#include "SharkWander.hpp"
#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkWander::entry(shark& entity) { entity.setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void SharkWander::exit(shark& entity) { entity.removeTint(); };

            void SharkWander::execute(shark& entity) {
                if (entity.shouldFlee()) {
                    entity.getStateMachine().changeState(std::make_unique<SharkFlee>(), entity);
                }
                else if (entity.shouldChase()) {
                    entity.getStateMachine().changeState(std::make_unique<SharkChase>(), entity);
                }
                else {
                    entity.moveRandomly();
                    entity.eatPig();
                }
            };

            std::string SharkWander::toString() { return "SharkWander"; };
        }
    }
}