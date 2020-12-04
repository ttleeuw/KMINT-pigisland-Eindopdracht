#include "BoatGlobalState.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatGlobalState::execute(boat* entity) {
                // TODO
                if (entity->getPaintDamage() >= STEPS_REQUIRED)
                {
                    entity->getStateMachine().changeState(new BoatRepair, entity);
                }
            };

            std::string BoatGlobalState::toString() { return "SharkWander"; };
        }
    }
}