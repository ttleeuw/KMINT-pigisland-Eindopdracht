#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"
namespace kmint {
    namespace pigisland {
        boat::boat(map::map_graph& g, map::map_node& initial_node, finitestate::ScoreCard& _scoreCard)
            : play::map_bound_actor{ initial_node }, graph(g), drawable_{ *this, graphics::image{boat_image()} }, scoreCard(_scoreCard)
        {
            this->stateMachine.setCurrentState(new finitestate::BoatWander, this);
            this->stateMachine.setGlobalState(new finitestate::BoatGlobalState);
        }


        void boat::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->stateMachine.update(this);

                t_passed_ = from_seconds(0);
            }
        }

        void boat::moveRandomly()
        {
            canMove = waitIfNecessary();
            if (canMove) {
                int next_index = random_int(0, this->node().num_edges());
                this->node(this->node()[next_index].to());
                waitTimer = this->node()[next_index].weight() - 1;
            }
        }

        bool boat::waitIfNecessary()
        {
            if (waitTimer <= 0) {
                return true;
            }
            waitTimer--;
            return false;
        }

    } // namespace pigisland
} // namespace kmint
