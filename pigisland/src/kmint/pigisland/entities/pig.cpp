#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location)
          : MovingEntity(location, *this, pig_image())
        {
        }

		void pig::move() {
           
		}

        void pig::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                //auto steeringForce = steeringBehaviour.calculate(*this);

                ////Acceleration = Force/Mass
                //this->setAcceleration(steeringForce);
                ////update velocity_
                //this->setVelocity(steeringForce);

                //this->setPosition(dt);

                //auto x = kmint::math::vector2d{ this->location().x(), this->location().y() };
                //auto r = x + this->position;
                //this->location(r);
                ////update the position
                ////move(velocity_ * to_seconds(dt));


                t_passed_ = from_seconds(0);
            }
        }
    } // namespace pigisland
} // namespace kmint
