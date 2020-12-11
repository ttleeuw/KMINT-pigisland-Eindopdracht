#include <iostream>

#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkGlobalState.hpp"
#include "kmint/pigisland/resources/resources.hpp"

namespace kmint {
    namespace pigisland {
        shark::shark(map::map_graph& g, map::map_node& initial_node)
            : MapActor{ g, initial_node, *this, graphics::image{shark_image()} }
        {
            this->stateMachine.setCurrentState(new finitestate::SharkWander, this);
            this->stateMachine.setGlobalState(new finitestate::SharkGlobalState);
        }

        void shark::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->stateMachine.update(this);

                t_passed_ = from_seconds(0);
            }
        }

        bool shark::shouldFlee() {
            // TODO 
            return false;
        }

        void shark::eatPig() {
            // TODO 
            for (std::size_t i = 0; i < this->num_colliding_actors(); ++i)
            {
                // TODO remove if pig
                auto& a = this->colliding_actor(i);
                a.remove();
            }
        }
    } // namespace pigisland
} // namespace kmint
