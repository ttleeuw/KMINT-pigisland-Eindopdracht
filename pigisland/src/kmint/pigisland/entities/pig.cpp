#include "kmint/pigisland/entities/pig.hpp"
#include "kmint/pigisland/resources/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/util/WallFactory.hpp"
#include <kmint/pigisland/entities/properties/PigPropertiesDefault.hpp>
#include <kmint/pigisland/entities/properties/PigPropertiesGenetic.hpp>

namespace kmint {
    namespace pigisland {
        pig::pig(math::vector2d location, boat& boat, shark& shark) : MovingEntity(location, *this, pig_image(), boat, shark)
        {
            this->_heading = { random_scalar(-1, 1), random_scalar(-1, 1) };
            this->_side = { random_scalar(-1, 1), random_scalar(-1, 1) };
            velocity = math::vector2d(random_scalar(-0.1, 0.1), random_scalar(-0.1, 0.1));
            this->properties = std::make_unique< PigPropertiesDefault>(boat, shark);
        }

        pig::pig(math::vector2d location, boat& boat, shark& shark, geneticalgorithm::Chromosome _chromosome) : MovingEntity(location, *this, pig_image(), boat, shark), chromosome(_chromosome)
        {
            this->_heading = { random_scalar(-1, 1), random_scalar(-1, 1) };
            this->_side = { random_scalar(-1, 1), random_scalar(-1, 1) };
            velocity = math::vector2d(random_scalar(-0.1, 0.1), random_scalar(-0.1, 0.1));
            this->properties = std::make_unique<PigPropertiesGenetic>(boat, shark);
            auto prop = dynamic_cast<PigPropertiesGenetic*>(this->properties.get());
            prop->setSeekWeight(chromosome.get()[0]);
            prop->setFleeWeight(chromosome.get()[1]);
            prop->setCohesionWeight(chromosome.get()[2]);
            prop->setSeparationWeight(chromosome.get()[3]);
            prop->setAlignmentWeight(chromosome.get()[4]);
        }


        void pig::act(delta_time dt) {
            t_passed_ += dt;
            if (to_seconds(t_passed_) >= 1) {
                auto steeringForce = steeringBehaviour.calculate(*this);
                //Acceleration = Force/Mass
                kmint::math::vector2d acceleration = steeringForce / mass();
                //update velocity
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
