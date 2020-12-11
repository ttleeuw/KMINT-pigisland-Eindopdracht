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

			  // als incorporeal false is, doet de actor mee aan collision detection
			  bool incorporeal() const override { return false; }
			  // geeft de lengte van een zijde van de collision box van deze actor terug.
			  // Belangrijk voor collision detection
			  scalar collision_range() const override { return 16.0; }
		private:
			play::image_drawable drawable_;
		};
	} 
} 
#endif 
