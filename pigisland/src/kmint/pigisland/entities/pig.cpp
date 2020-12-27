#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location, boat& boat, shark& shark)
          : MovingEntity(location, *this, pig_image(), boat, shark)
        {
            this->_heading = { random_scalar(-1, 1), random_scalar(-1, 1) };
            this->_side = { random_scalar(-1, 1), random_scalar(-1, 1) };
            velocity = math::vector2d(random_scalar(-0.0008, 0.0008), random_scalar(-0.0008, 0.00080));
        }

        void pig::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                auto steeringForce = steeringBehaviour.calculate(*this);

                //Acceleration = Force/Mass
                kmint::math::vector2d acceleration = steeringForce / mass();
                //update velocity_
                velocity += acceleration * to_seconds(dt);
                velocity = kmint::pigisland::util::math::Util::truncate(velocity, maxSpeed());

                //update the position
                location(location() + (velocity * to_seconds(dt)));
                //update the heading if the vehicle has a non zero velocity
                if (kmint::pigisland::util::math::Util::calcVectorLength(velocity) > 0.00000001)
                {
                    this->_heading = normalize(velocity);
                    this->_side = kmint::pigisland::util::math::Util::perpendicular(this->_heading);
                }

                t_passed_ = from_seconds(0);
            }
        }
    } // namespace pigisland
} // namespace kmint
