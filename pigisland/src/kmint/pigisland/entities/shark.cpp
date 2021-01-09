#include <iostream>

#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include <kmint/pigisland/entities/pig.hpp>
#include <kmint/pigisland/entities/boat.hpp>

namespace kmint {
    namespace pigisland {
        shark::shark(map::map_graph& g, map::map_node& initial_node)
            : MapActor{ g, initial_node, *this, graphics::image{shark_image()} }
        {
            this->stateMachine.setCurrentState(std::make_unique<finitestate::SharkWander>(), *this);
            this->stateMachine.setGlobalState(std::make_unique<finitestate::SharkGlobalState>(), *this);
        }
        shark::shark(map::map_graph& g, map::map_node& initial_node, geneticalgorithm::GeneticScoreCard& _geneticScoreCard)
            : MapActor{ g, initial_node, *this, graphics::image{shark_image()} }, geneticScoreCard{ &_geneticScoreCard }
        {
            this->stateMachine.setCurrentState(std::make_unique<finitestate::SharkWander>(), *this);
            this->stateMachine.setGlobalState(std::make_unique<finitestate::SharkGlobalState>(), *this);
        }

        void shark::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->stateMachine.update(*this);

                t_passed_ = from_seconds(0);
            }
        }

        bool shark::shouldFlee() {
            for (std::size_t i = 0; i < this->num_perceived_actors(); ++i)
            {
                auto& actor = this->perceived_actor(i);
                if (typeid(actor) == typeid(boat)) {
                    return true;
                }
            }
            return false;
        }

        bool shark::shouldChase() {
            for (std::size_t i = 0; i < this->num_perceived_actors(); ++i) {
                kmint::play::actor& a = this->perceived_actor(i);

                if (!a.removed()) {
                    return true;
                }
            }
            return false;
        }

        void shark::reset() {
            this->node(initial);
            this->steps = 0;
            this->resting = false;
            this->stateMachine.changeState(std::make_unique<finitestate::SharkWander>(), *this);
            this->stateMachine.setGlobalState(std::make_unique<finitestate::SharkGlobalState>(), *this);
        }

        void shark::eatPig() {
            for (std::size_t i = 0; i < this->num_colliding_actors(); ++i)
            {
                auto& actor = this->colliding_actor(i);
                if (typeid(actor) == typeid(pig)) {
                    auto p = dynamic_cast<pig*>(&actor);
                    if (geneticScoreCard) geneticScoreCard->saveLeastFittestChromosome(p->getChromosome());
                    actor.remove();
                }
            }
        }
    }
} 