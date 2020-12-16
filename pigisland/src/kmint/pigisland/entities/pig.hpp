#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>

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
		private:
			play::image_drawable drawable_;
		};
	} 
} 
#endif 
