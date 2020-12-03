#include "SharkGlobalState.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkGlobalState::execute(shark* entity) {
                if (entity->getSteps() == STEPS_REQUIRED_TIRED) 
                {
                    entity->changeState(new SharkTired);
                }
                else 
                {
                    entity->increaseSteps();
                }
            }

            std::string SharkGlobalState::getState() { return "SharkGlobalState"; }
        }
    }
}