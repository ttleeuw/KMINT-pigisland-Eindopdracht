#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.hpp"

namespace kmint {
	namespace pigisland {
		class MovingEntity : public play::free_roaming_actor {
		public:
			MovingEntity(math::vector2d location, play::actor const& owner, graphics::image image)
				: play::free_roaming_actor{ location }, drawable_{ owner, image }
			{
			}

			const ui::drawable& drawable() const override { return drawable_; }

			bool incorporeal() const override { return false; }
			scalar collision_range() const override { return 16.0; }

			bool perceptive() const override { return true; }
			scalar perception_range() const override { return 200.f; }

			virtual void move() = 0;

			virtual void act(delta_time dt) override = 0;

			math::vector2d& getTarget() { return this->target; }

			void setAcceleration(math::vector2d steeringForce) {
				acceleration = steeringForce / mass;
			}

			void setVelocity(math::vector2d v) {
				auto l = calcVectorLength(v);
				velocity = truncate(velocity, maxSpeed);
			}

			void setPosition(delta_time dt) {
				position += velocity * dt.count();
			}

			double calcVectorLength(kmint::math::vector2d target) {
				return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
			}

			kmint::math::vector2d truncate(kmint::math::vector2d vector, float max)
			{
				auto length = calcVectorLength(vector);
				if (length > max)
				{
					auto result = normalize(vector);

					return result *= max;
				}
				return vector;
			}

			kmint::math::vector2d normalize(kmint::math::vector2d target)
			{
				double vector_length = calcVectorLength(target);

				if (vector_length > std::numeric_limits<double>::epsilon())
				{
					target.x(target.x() / vector_length);
					target.y(target.y() / vector_length);
				}
				return target;
			}

			math::vector2d side() const { return { 1.0, 0.0 }; }
		protected:
			float mass; // const
			float force; // var
			float maxForce;
			float maxTurnRate;
			float maxSpeed;

			math::vector2d acceleration; // calculated
			math::vector2d velocity; // calculated
			math::vector2d maxVelocity; // calculated
			math::vector2d position; // calculated

			math::vector2d target;
			forcedrivenentities::SteeringBehaviours steeringBehaviour;

			delta_time t_passed_{};
			play::image_drawable drawable_;
		};
	} // namespace pigisland
} // namespace kmint
