#include "SharkFlee.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkFlee::entry(shark& entity) { entity.setTint(kmint::graphics::color(25, 255, 140, 0)); };
            void SharkFlee::exit(shark& entity) { entity.removeTint(); };

            void SharkFlee::execute(shark& entity) {
                entity.moveRandomly();
                steps++;
                if (steps == MAX_STEPS) {
                    entity.getStateMachine().changeState(std::make_unique<SharkWander>(), entity);
                }
            };

            std::string SharkFlee::toString() { return "SharkFlee"; };
        }
    }
}