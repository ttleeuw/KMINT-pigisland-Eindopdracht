#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"
#include <kmint/pigisland/entities/pig.hpp>

namespace kmint {
    namespace pigisland {
        boat::boat(map::map_graph& g, map::map_node& initial_node, finitestate::BoatDockingScoreCard& _scoreCard)
            : MapActor{ g, initial_node, *this, graphics::image{boat_image()} }, scoreCard(_scoreCard)
        {
            this->stateMachine.setCurrentState(std::make_unique<finitestate::BoatWander>(), *this);
            this->stateMachine.setGlobalState(std::make_unique<finitestate::BoatGlobalState>(), *this);
        }


        void boat::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->stateMachine.update(*this);
                t_passed_ = from_seconds(0);
            }
        }

        void boat::repair(DockingStation dockingStation, int repairValue) {
            scoreCard.dock(dockingStation, repairValue);
            steps -= repairValue;
        }

        void boat::reset() { }

        void boat::savePig() {
            for (std::size_t i = 0; i < this->num_colliding_actors(); ++i)
            {
                auto& actor = this->colliding_actor(i);
                if (typeid(actor) == typeid(pig)) {
                    actor.remove();
                }
            }
        }
    } // namespace pigisland
} // namespace kmint
