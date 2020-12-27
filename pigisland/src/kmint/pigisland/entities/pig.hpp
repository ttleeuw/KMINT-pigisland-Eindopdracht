#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include "kmint/pigisland/entities/base/MovingEntity.hpp"

namespace kmint {
	namespace pigisland {
		class pig : public MovingEntity {
		public:
			pig::pig(math::vector2d location, boat& boat, shark& shark);

			void act(delta_time dt) override;
		};
	} 
} 
#endif 
