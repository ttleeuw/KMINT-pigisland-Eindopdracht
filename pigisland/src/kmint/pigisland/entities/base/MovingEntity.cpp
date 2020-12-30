#include "kmint/pigisland/entities/base/MovingEntity.hpp"
#include "kmint/pigisland/util/WallFactory.hpp"

namespace kmint {
	namespace pigisland {
		MovingEntity::MovingEntity(math::vector2d location, play::actor const& owner, graphics::image image, boat& boat, shark& shark)
			: play::free_roaming_actor{ location }, drawable_{ owner, image }, _fleeTarget{ shark }, _persuitTarget{ boat }
		{
			this->walls = pigisland::WallFactory::create();
		}
	} // namespace pigisland
} // namespace kmint
