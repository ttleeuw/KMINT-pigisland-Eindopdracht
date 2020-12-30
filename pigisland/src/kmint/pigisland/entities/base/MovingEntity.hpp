#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/util/math.hpp"
#include "kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.hpp"

#include "kmint/pigisland/entities/boat.hpp"
#include "kmint/pigisland/entities/shark.hpp"

#include "kmint/pigisland/util/Wall2D.hpp"
#include <kmint/pigisland/entities/properties/IProperties.hpp>

namespace kmint {
	namespace pigisland {
		class MovingEntity : public play::free_roaming_actor {
		public:
			MovingEntity(math::vector2d location, play::actor const& owner, graphics::image image, boat& boat, shark& shark);

			const ui::drawable& drawable() const override { return drawable_; }

			bool incorporeal() const override { return false; }
			scalar collision_range() const override { return 16.0; }

			bool perceptive() const override { return true; }
			scalar perception_range() const override { return 200.f; }

			std::vector<Wall2D> getWalls() { return this->walls; };

			virtual void act(delta_time dt) override = 0;

			kmint::math::vector2d getVelocity() { return this->velocity; }

			//NOTE: these weight modifiers are used to tweak
			double wanderJitter() const { return this->properties->wanderJitter(); }
			double wanderRadius() const { return this->properties->wanderRadius(); }
			double wanderDistance() const { return this->properties->wanderDistance(); }

			double separationWeight() const { return this->properties->separationWeight(); }
			double cohesionWeight() const { return this->properties->cohesionWeight(); }
			double alignmentWeight() const { return this->properties->alignmentWeight(); }

			double seekWeight() const { return this->properties->seekWeight(); }
			double wanderWeight() const { return this->properties->wanderWeight(); }
			double fleeWeight() const { return this->properties->fleeWeight(); }
			
			double wallDetectionFeelerLength() const { return this->properties->wallDetectionFeelerLength(); }
			float obstacleAvoidanceWeight() const { return this->properties->obstacleAvoidanceWeight(); }

			float mass() const { return this->properties->mass(); }
			float getForce() const { return this->force; }
			float maxForce() const { return this->properties->maxForce(); }
			float maxTurnRate() const { return this->properties->maxTurnRate(); }
			float maxSpeed() const { return this->properties->maxSpeed(); }

			kmint::play::actor& persuitTarget() const { return this->properties->persuitTarget(); };
			kmint::play::actor& fleeTarget() const { return this->properties->fleeTarget(); };

			kmint::math::vector2d heading() const override { return _heading; }
			kmint::math::vector2d side() const { return _side; }
		protected:
			float force;

			kmint::math::vector2d _heading;
			kmint::math::vector2d _side;

			kmint::play::actor& _persuitTarget;
			kmint::play::actor& _fleeTarget;

			kmint::math::vector2d velocity; 

			std::vector<Wall2D> walls;
			std::unique_ptr<IProperties> properties;

			forcedrivenentities::SteeringBehaviours steeringBehaviour;

			delta_time t_passed_{};
			play::image_drawable drawable_;
		};
	} // namespace pigisland
} // namespace kmint
