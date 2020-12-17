#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location)
          : play::free_roaming_actor{location}, drawable_{*this, pig_image()} 
        {
			
        }

		void pig::move() {
            steeringBehaviour.cohesion(*this);
		}

        void pig::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                this->move();
                t_passed_ = from_seconds(0);
            }
        }
    } // namespace pigisland
} // namespace kmint
