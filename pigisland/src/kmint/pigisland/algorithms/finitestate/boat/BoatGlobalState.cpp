#include "BoatGlobalState.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatGlobalState::execute(boat* entity) {
                // TODO
                if (entity->getPaintDamage() >= MAX_PAINT_DAMAGE)
                {
                    entity->changeState(new BoatRepair);
                }
            };

            std::string BoatGlobalState::getState() { return "SharkWander"; };
        }
    }
}