#include <iostream>

#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkGlobalState.hpp"
#include "kmint/pigisland/resources/resources.hpp"

namespace kmint {
    namespace pigisland {
        shark::shark(map::map_graph &g, map::map_node &initial_node)
            : play::map_bound_actor{initial_node}, graph(g), initial(initial_node), drawable_{*this, graphics::image{ shark_image()} }
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
    } // namespace pigisland
} // namespace kmint
