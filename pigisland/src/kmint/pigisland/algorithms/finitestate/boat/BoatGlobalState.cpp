#include "BoatGlobalState.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatGlobalState::execute(boat* entity) {
                if (entity->getPaintDamage() == STEPS_REQUIRED)
                {
                    entity->getStateMachine().changeState(new BoatRepair, entity);
                }
                else
                {
                    entity->increasePaintDamage();
                }
            };
        }
    }
}