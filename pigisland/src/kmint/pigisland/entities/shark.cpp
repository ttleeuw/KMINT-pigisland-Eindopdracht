#include <iostream>

#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
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
            for (std::size_t i = 0; i < this->num_perceived_actors(); ++i)
            {
                auto& a = this->perceived_actor(i);
                // TODO check if boat
                int k = 0;
            }
            return false;
        }

        void shark::reset() {
            this->node(initial);
            this->steps = 0;
            this->resting = false;
            this->stateMachine.changeState(new finitestate::SharkWander, this);
            this->stateMachine.setGlobalState(new finitestate::SharkGlobalState);
        }

        void shark::eatPig() {
            for (std::size_t i = 0; i < this->num_colliding_actors(); ++i)
            {
                auto& actor = this->colliding_actor(i);
                // TODO check if pig
                actor.remove();
            }
        }
    }
} 