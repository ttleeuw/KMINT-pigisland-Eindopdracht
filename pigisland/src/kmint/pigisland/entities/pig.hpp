#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include "kmint/pigisland/algorithms/forcedrivenentities/SteeringBehaviours.hpp"

namespace kmint {
	namespace pigisland {
		class pig : public play::free_roaming_actor {
		public:
			  pig(math::vector2d location);
			  const ui::drawable &drawable() const override { return drawable_; }

			  bool incorporeal() const override { return false; }
			  scalar collision_range() const override { return 16.0; }

			  bool perceptive() const override { return true; }
			  scalar perception_range() const override { return 200.f; }

			  void move();

			  void act(delta_time dt) override;

			  math::vector2d& getTarget() { return this->target; }
		private:
			delta_time t_passed_{};
			math::vector2d target;
			play::image_drawable drawable_;
			forcedrivenentities::SteeringBehaviours steeringBehaviour;
		};
	} 
} 
#endif 
