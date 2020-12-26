#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location)
          : MovingEntity(location, *this, pig_image())
        {
			mass = 1;
			maxSpeed = 40;
			maxForce = 100;
			//NOTE: these weight modifiers are used to tweak
            /* 
            seekWeight = 35;
            wanderWeight = 8;
            
            fleeWeigths
            persuitWeight = 35;
           

            separationWeight = 10;
            cohesionWeight = 0.125;
            alignmentWeight = 7.5;*/
        }

		void pig::move() {
            auto x = steeringBehaviour.calculate(*this);
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
