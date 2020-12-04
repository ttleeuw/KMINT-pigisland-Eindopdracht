#include "SharkGlobalState.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkGlobalState::execute(shark* entity) {
                if (entity->getSteps() == STEPS_REQUIRED)
                {
                    entity->getStateMachine().changeState(new SharkTired, entity);
                }
                else 
                {
                    entity->increaseSteps();
                }
            }

            std::string SharkGlobalState::toString() { return "SharkGlobalState"; }
        }
    }
}