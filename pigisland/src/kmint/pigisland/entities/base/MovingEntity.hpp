#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/util/math.hpp"
#include "kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.hpp"

#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/shark.hpp"

namespace kmint {
	namespace pigisland {
		class MovingEntity : public play::free_roaming_actor {
		public:
			MovingEntity(math::vector2d location, play::actor const& owner, graphics::image image, boat& boat, shark& shark)
				: play::free_roaming_actor{ location }, drawable_{ owner, image }, _fleeTarget{shark}, _persuitTarget{boat}
			{
			}

			const ui::drawable& drawable() const override { return drawable_; }

			bool incorporeal() const override { return false; }
			scalar collision_range() const override { return 16.0; }

			bool perceptive() const override { return true; }
			scalar perception_range() const override { return 200.f; }

			virtual void move() = 0;

			virtual void act(delta_time dt) override = 0;

			kmint::math::vector2d getVelocity() { return this->velocity; }

			kmint::math::vector2d getTarget() { return this->target; }

			//NOTE: these weight modifiers are used to tweak
			double wanderJitter() const { return 1; }
			double wanderRadius() const { return 1; }
			double wanderDistance() const { return 1; }

			double separationWeight() const { return 1; }
			double cohesionWeight() const { return 5; }
			double alignmentWeight() const { return 1; }

			double seekWeight() const { return 1; }
			double persuitWeight() const { return 1; }
			double wanderWeight() const { return 1; }
			double fleeWeight() const { return 1; }

			float mass() const { return 1; }
			float getForce() const { return this->force; }
			float maxForce() const { return 10; }
			float maxTurnRate() const { return 1; }
			float maxSpeed() const { return 1; }

			kmint::play::actor& persuitTarget() { return this->_persuitTarget; };
			kmint::play::actor& fleeTarget() { return this->_fleeTarget; };

			kmint::math::vector2d heading() const override { return _heading; }
			kmint::math::vector2d side() const { return _side; }
		protected:
			float force;

			kmint::math::vector2d _heading;
			kmint::math::vector2d _side;

			kmint::play::actor& _persuitTarget;
			kmint::play::actor& _fleeTarget;


			kmint::math::vector2d velocity; // calculated


			forcedrivenentities::SteeringBehaviours steeringBehaviour;

			kmint::math::vector2d target;

			delta_time t_passed_{};
			play::image_drawable drawable_;
		};
	} // namespace pigisland
} // namespace kmint
