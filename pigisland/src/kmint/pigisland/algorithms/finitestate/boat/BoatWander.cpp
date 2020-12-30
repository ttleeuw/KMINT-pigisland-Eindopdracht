#include "BoatWander.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatWander::entry(boat& entity) { entity.setTint(kmint::graphics::color(128, 128, 255, 0)); };
            void BoatWander::exit(boat& entity) { entity.removeTint(); };

            void BoatWander::execute(boat& entity) {
                entity.moveRandomly();
                entity.savePig();
            };

            std::string BoatWander::toString() { return "BoatWander"; };
        }
    }
}