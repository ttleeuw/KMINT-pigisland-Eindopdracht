#include "SharkGlobalState.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
    namespace pigisland {
        namespace finitestate {
            void SharkGlobalState::entry(shark& entity) {
                this->steps = 100;
            }

            void SharkGlobalState::exit(shark& entity) {
                this->steps = 0;
            }

            void SharkGlobalState::execute(shark& entity) {
                if (entity.getSteps() == steps)
                {
                    entity.getStateMachine().changeState(std::make_unique<SharkTired>(), entity);
                }
                else 
                {
                    entity.increaseSteps();
                }
            }
        }
    }
}