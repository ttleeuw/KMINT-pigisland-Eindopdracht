#include "BoatGlobalState.hpp"
#include "kmint/pigisland/entities/boat.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void BoatGlobalState::entry(boat& entity) {
                this->steps = 100;
            }

            void BoatGlobalState::exit(boat& entity) {
                this->steps = 0;
            }

            void BoatGlobalState::execute(boat& entity) {
                if (entity.getPaintDamage() >= steps)
                {
                    if(!repair)
                        entity.getStateMachine().changeState(std::make_unique<BoatRepair>(), entity);
                    repair = true;
                }
                else
                {
                    repair = false;
                    entity.increasePaintDamage();
                }
            };
        }
    }
}