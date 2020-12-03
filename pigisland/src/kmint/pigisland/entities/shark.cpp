#include "kmint/pigisland/entities/shark.hpp"
#include "kmint/pigisland/algorithms/node_algorithm.hpp"
#include "kmint/pigisland/algorithms/finitestate/shark/SharkWander.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include <iostream>

namespace kmint {
    namespace pigisland {
        shark::shark(map::map_graph &g, map::map_node &initial_node)
            : play::map_bound_actor{initial_node}, graph(g), initial(initial_node), drawable_{*this, graphics::image{ shark_image()} }
        {
            this->currentState = new finitestate::SharkWander;
            this->globalState = new finitestate::SharkGlobalState;
            this->currentState->entry(this);
        }

        void shark::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->currentState->execute(this);
                this->globalState->execute(this);

                t_passed_ = from_seconds(0);
            }
        }
    } // namespace pigisland
} // namespace kmint
