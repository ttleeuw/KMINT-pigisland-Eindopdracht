#pragma once
#include <queue>
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace kmint {
	namespace pigisland {
		class MovingEntity : public  play::free_roaming_actor {
		public:
			MovingEntity(math::vector2d location, play::actor const& owner, graphics::image image)
				: play::free_roaming_actor{ location }, drawable_{ owner, image) }
			{
			}

			const ui::drawable& drawable() const override { return drawable_; }

			bool incorporeal() const override { return false; }
			scalar collision_range() const override { return 16.0; }

			bool perceptive() const override { return true; }
			scalar perception_range() const override { return 200.f; }

			void move() = 0;

			virtual void act(delta_time dt) override = 0;

			math::vector2d& getTarget() { return this->target; }
		protected:
			delta_time t_passed_{};
			math::vector2d target;
			play::image_drawable drawable_;
			forcedrivenentities::SteeringBehaviours steeringBehaviour;
	} // namespace pigisland
} // namespace kmint
